#include <iostream>
#include <string>

#include "gameserver.hpp"

int main(int argc, char *argv[]) {
   CubeZoneGameServer server;

   server.init();
   server.start();
}