#include "connected_client.h"
#include <iostream>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>

ConnectedClient::ConnectedClient(int socket) : socket(socket), isRunning(true)
{
    clientThread = std::thread(&ConnectedClient::ListenLoop, this);
}

void ConnectedClient::StartListening()
{
    clientThread.join();
}

void ConnectedClient::ListenLoop()
{
    char buffer[256];
    while (isRunning)
    {
        int n = read(socket, buffer, sizeof(buffer) - 1);
        if (n <= 0)
        {
            std::cerr << "Client disconnected or read error" << std::endl;
            break;
        }

        buffer[n] = '\0';
        std::cout << "Message received from client " << socket << ": " << buffer << std::endl;

        // Handle the received message here
    }

    Close();
}

void ConnectedClient::Send(const std::string &message)
{
    std::lock_guard<std::mutex> lock(sendMutex);
    int n = write(socket, message.c_str(), message.size());
    if (n < 0)
    {
        std::cerr << "Error sending to client " << socket << std::endl;
    }
}

void ConnectedClient::Close()
{
    isRunning = false;
    close(socket);
}
