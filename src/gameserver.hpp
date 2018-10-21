#pragma once

#include <vector>
#include <map>

#include "game.hpp"
#include "servercube.hpp"

class CubeZoneGameServer {
    public:
        CubeZoneGameServer(unsigned short port);
        ~CubeZoneGameServer();

        void init();
        void start();

        void processPacket(sf::Packet p, sf::IpAddress ip, unsigned short port);

        void sendId(sf::IpAddress from, unsigned short port);
        void sendUpdate(sf::IpAddress from, unsigned short port);
        void updateCube(sf::Packet p, sf::IpAddress from, unsigned short port);
    private:
        unsigned short mPort;
        sf::UdpSocket mListenSocket;
        sf::Packet mDataPacket;

        std::map<unsigned int, ServerCube> mCubeMap;
        sf::Uint64 mNextId;
};