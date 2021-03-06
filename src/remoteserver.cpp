#include <iostream>

#include "remoteserver.hpp"

RemoteServer::RemoteServer(sf::IpAddress ip, unsigned short port)
: mIp {ip}
, mPort {port}
, mCube {nullptr}
, mId {0}
, mConnected {false}
{
}

bool RemoteServer::isConnected() {
    return mConnected;
}

void RemoteServer::setCube(Cube* cube) {
    mCube = cube;
}

void RemoteServer::setMap(std::map<unsigned int, std::shared_ptr<Cube>>* map) {
    mCubeMap = map;
}

void RemoteServer::connect() {
    getId();
    if (mId != 0) {
        mConnected = true;
        mSocket.setBlocking(false);
    }
}

void RemoteServer::tick() {
    sendUpdate();
    getUpdate();
}

void RemoteServer::getId() {
    if (mId == 0) {
        mPacket.clear();
        mPacket << "getid";

        mSocket.send(mPacket, mIp, mPort);

        std::cout << "Sent request for id, waiting for response...\n";

        mSocket.receive(mPacket, mReceiveIp, mReceivePort);

        mPacket >> mId;

        std::cout << "Got ID from " << mReceiveIp << ":" << mReceivePort << ": " << mId << std::endl;
    } else {
        std::cout << "You already have an id and it's " << mId << std::endl;
    }
}

void RemoteServer::sendUpdate() {
    if (mId == 0) {
        return;
    } else {
        mPacket.clear();
        mPacket << "sendupdate"
            << mId
            << mCube->getPosition().x << mCube->getPosition().y 
            << mCube->getColor().r << mCube->getColor().g << mCube->getColor().b;

        mSocket.send(mPacket, mIp, mPort);

        std::cout << "Sent update.\n";
    }
}

void RemoteServer::getUpdate() {
    if (mId == 0) {
        return;
    } else {
        mPacket.clear();
        mPacket << "getupdate"
            << mId;

        mSocket.send(mPacket, mIp, mPort);

        std::cout << "Sent request for game update.\n";

        sf::Socket::Status s = mSocket.receive(mPacket, mReceiveIp, mReceivePort);

        if (s != sf::Socket::Done) {
            std::cout << "Error receiving game update: ";

            switch (s) {
                case sf::Socket::NotReady:
                    std::cout << "Not Ready";
                    break;
                case sf::Socket::Partial:
                    std::cout << "Partial";
                    break;
                case sf::Socket::Disconnected:
                    std::cout << "Diconnected";
                    break;
                case sf::Socket::Error:
                    std::cout << "Error";
                    break;
            }

            std::cout << "\n";

            return;
        }

        sf::Int64 n;
        mPacket >> n; // number of cubes

        std::cout << "Recieved " << n << " cubes.\n";

        sf::Int64 x, y;
        sf::Uint8 r, g, b;

        for (int i = 0; i < n; i++) {
            sf::Uint64 nid;
            mPacket >> nid;
            std::cout << "Updating cube " << nid << "\n";

            unsigned int id = nid;

            if (id == mId) {
                // don't do anything with my cube
                std::cout << "Skipping cube " << id << std::endl;
                // dump packet
                mPacket >> x >> y >> r >> g >> b;
                continue;
            }

            if (!mCubeMap->count(id)) {
                (*mCubeMap)[id] = std::shared_ptr<Cube>(new Cube(nullptr));
            }
            
            Cube& cube = *mCubeMap->at(id);

            mPacket >> x >> y;
            cube.setPosition(x, y);

            mPacket >> r >> g >> b;
            cube.setColor(sf::Color(r, g, b));

            // cube is alive. update time to live.
            cube.resetTimeToLive();
        }

        // delete any disconnected cubes
        for (auto pair : *mCubeMap) {
            Cube& cube = *pair.second;
            cube.decrementTimeToLive();

            if (cube.getTimeToLive() < 0) {
                mCubeMap->erase(pair.first);
                std::cout << "Deleted cube with id " << pair.first << "\n";
            }
        }
    }
}

void RemoteServer::disconnect() {
    mPacket.clear();

    mPacket << "disconnect" << mId;

    mSocket.send(mPacket, mIp, mPort);

    mConnected = false;
}