#include <iostream>
#include <string>

#include "game.hpp"

int main(int argc, char *argv[]) {
    unsigned short port;
    sf::IpAddress ip;
    
    if (argc < 3) {
        port = 3001;
    } else {
        port = std::atoi(argv[2]);
    }

    if (argc < 2) {
        ip = "localhost";
    } else {
        ip = argv[1];
    }
    
    CubeZoneGame game(ip, port);

    std::cout << "External server is " << ip << ":" << port << ".\n"
        << "Press R to connect.\n";

    game.init();
    game.run();
}