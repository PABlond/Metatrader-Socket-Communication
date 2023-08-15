#pragma once
#include "connected_client.h"
#include <netinet/in.h>
#include <vector>
#include <thread>
#include <mutex>
#include <memory>

class Server
{
public:
    Server(int port);
    ~Server();

    void Start();

private:
    int sockfd;
    int portno;
    sockaddr_in serv_addr;

    std::vector<std::shared_ptr<ConnectedClient>> clients;
    std::mutex clientsMutex;

    void HandleClientConnection(int newsockfd);
};
