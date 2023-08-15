#include "server.h"
#include "connected_client.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

Server::Server(int port) : portno(port)
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        std::cerr << "Error creating socket" << std::endl;
        exit(1);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "Error binding socket to port" << std::endl;
        exit(1);
    }
}

Server::~Server()
{
    close(sockfd);
}

void Server::Start()
{
    listen(sockfd, 5);
    std::cout << "Server is now listening on port: " << portno << std::endl;
    while (true)
    {
        sockaddr_in cli_addr;
        socklen_t clilen = sizeof(cli_addr);

        int newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
        if (newsockfd < 0)
        {
            std::cerr << "Error accepting connection" << std::endl;
            continue;
        }

        HandleClientConnection(newsockfd);
    }
}

void Server::HandleClientConnection(int newsockfd)
{
    std::lock_guard<std::mutex> lock(clientsMutex);
    clients.emplace_back(std::make_shared<ConnectedClient>(newsockfd));
    clients.back()->Send("account:data");
    clients.back()->StartListening();
}
