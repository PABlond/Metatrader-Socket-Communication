#pragma once

#include <string>
#include <thread>
#include <mutex>

class ConnectedClient {
public:
    ConnectedClient(int socket);
    void StartListening();
    void Send(const std::string& message);
    void Close();

private:
    int socket;
    std::thread clientThread;
    std::mutex sendMutex;
    bool isRunning;

    void ListenLoop();
};
