#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "gameobject.hpp"
#include "remoteserver.hpp"

class CubeZoneGame {
    friend class GameObject;
    friend class Cube;
    public:
        CubeZoneGame();
        ~CubeZoneGame();

        bool init();
        bool run();

        bool addGameObject(GameObject* obj);
    private:
        sf::RenderWindow mRenderWindow;
        sf::RenderTexture mRenderTexture;
        sf::Sprite mTex;
        std::vector<std::shared_ptr<GameObject>> mGameObjects;
        std::vector<std::shared_ptr<DrawableGameObject>> mDrawableGameObjects;
        std::map<unsigned int, std::shared_ptr<Cube>> mNetworkCubes;
        RemoteServer mRemoteServer;
};