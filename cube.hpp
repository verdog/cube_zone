#pragma once

#include <stdlib.h>
#include <time.h>

#include <SFML/Graphics.hpp>

#include "gameobject.hpp"

class Cube : public DrawableGameObject {
    public:
        Cube(CubeZoneGame *game);
        ~Cube() noexcept;

        void move(int x, int y);

        void handleInput();
        void update();

        void draw(sf::RenderTarget &target, sf::RenderStates) const;
    private:
        sf::RectangleShape mRect;
        sf::Vector2f mVelocity;
        sf::Color mColor;
        int mX, mY;
};