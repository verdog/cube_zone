#pragma once

#include <memory>

#include <SFML/Network.hpp>

#include "cube.hpp"

class RemoteServer {
    public:
        RemoteServer(sf::IpAddress ip, unsigned short port);

        bool isConnected();

        void setCube(Cube* cube);
        void setMap(std::map<unsigned int, std::shared_ptr<Cube>>* map);

        void connect();
        void tick();

        void sendUpdate();
        void getUpdate();
        void disconnect();
    private:
        sf::UdpSocket mSocket;
        sf::Packet mPacket;
        unsigned short mPort;
        unsigned short mReceivePort;
        sf::IpAddress mIp;
        sf::IpAddress mReceiveIp;
        unsigned int mId;

        Cube* mCube;
        std::map<unsigned int, std::shared_ptr<Cube>>* mCubeMap;

        bool mConnected;

        void getId();
};