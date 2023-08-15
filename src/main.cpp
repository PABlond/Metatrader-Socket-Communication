#include "server.h"

int main() {
    Server server(5555);
    server.Start();

    return 0;
}