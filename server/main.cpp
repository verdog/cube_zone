#include <iostream>
#include <string>

#include "gameserver.hpp"

int main(int argc, char *argv[]) {
    unsigned short port;

    if (argc < 2) {
        port = 3001;
    } else {
        port = std::atoi(argv[1]);
    }

   CubeZoneGameServer server(port);

   server.init();
   server.start();
}