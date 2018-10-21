    #include <iostream>
#include <map>

#include "gameserver.hpp"
#include "servercube.hpp"

using CZGS = CubeZoneGameServer;

CZGS::CubeZoneGameServer(short unsigned port)
: mPort {port}
, mNextId {1}
{
}

CZGS::~CubeZoneGameServer() = default;

void CZGS::init() {
    if (mListenSocket.bind(mPort) != sf::Socket::Done) {
        std::cerr << "Couldn't bind server!\n";
        return;
    }
}

void CZGS::start() {
    while (true) {

        std::cout << "Listening on port " << mPort << "...\n";

        sf::IpAddress sender;
        unsigned short port;
        if (mListenSocket.receive(mDataPacket, sender, port) != sf::Socket::Done) {
            std::cerr << "Error upon receiving!\n";
        }
        std::cout 
            << "Received a packet" 
            << " from " << sender 
            << " on port " << port 
            << std::endl;

        processPacket(mDataPacket, sender, port);
    }
}

void CZGS::processPacket(sf::Packet p, sf::IpAddress from, unsigned short port) {
    std::string purposeString;
    p >> purposeString;

    if (purposeString == "getid") {
        sendId(from, port);
    } else if (purposeString == "sendupdate") {
        updateCube(p, from, port);
    } else if (purposeString == "getupdate") {
        sendUpdate(from, port);
    } else {
        std::cout << "Error!\n";
    }
}

void CZGS::sendId(sf::IpAddress from, unsigned short port) {
    std::cout << "Generating id...\n";

    sf::Packet responsePacket;
    
    responsePacket << mNextId;

    // create cube
    mCubeMap[mNextId] = ServerCube();
    mCubeMap[mNextId].setPosition(0, 0);
    
    mNextId++;

    mListenSocket.send(responsePacket, from, port);
}

void CZGS::sendUpdate(sf::IpAddress from, unsigned short port) {
    sf::Packet updatePacket;

    updatePacket << sf::Int64(mCubeMap.size());

    for (auto pair : mCubeMap) {
        ServerCube& cube = pair.second;
        updatePacket << sf::Uint64(pair.first); // id
        updatePacket << sf::Int64(cube.getPosition().x) << sf::Int64(cube.getPosition().y);
        sf::Color c = cube.getColor();
        updatePacket << sf::Uint8(c.r) << sf::Uint8(c.g) << sf::Uint8(c.b);
        std::cout << "Added cube (" << pair.first << ") to update packet.\n";
    }

    mListenSocket.send(updatePacket, from, port);

    std::cout << "Sent update packet.\n";
}

void CZGS::updateCube(sf::Packet p, sf::IpAddress from, unsigned short port) {
    std::cout << "Updating cube...\n";

    sf::Uint64 cubeId;

    p >> cubeId;

    if (mCubeMap.count(cubeId)) {
        ServerCube& cube = mCubeMap.at(cubeId);

        int x, y;
        p >> x >> y;
        cube.setPosition(x, y);

        sf::Uint8 r, g, b;
        p >> r >> g >> b;
        cube.setColor(sf::Color(r, g, b));
    } else {
        std::cout << "Didn't find a cube with ID: " << cubeId << std::endl;
    }
}