#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "gameobject.hpp"

class CubeZoneGame {
    friend GameObject;
    public:
        CubeZoneGame();
        ~CubeZoneGame();

        bool init();
        bool run();

        bool addGameObject(GameObject* obj);
    private:
        sf::RenderWindow mRenderwindow;
        std::vector<std::shared_ptr<GameObject>> mGameObjects;
        std::vector<std::shared_ptr<DrawableGameObject>> mDrawableGameObjects;
};