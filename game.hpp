#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

class CubeZoneGame {
    public:
        CubeZoneGame();
        ~CubeZoneGame();

        bool init();
        bool run();
    private:
        sf::RenderWindow mRenderwindow;
};