#pragma once

#include <SFML/Graphics.hpp>

#include "gameobject.hpp"

class Cube : public DrawableGameObject {
    public:
        Cube(CubeZoneGame *game);
        ~Cube() noexcept;

        void draw(sf::RenderTarget &target, sf::RenderStates) const;
    private:
        sf::RectangleShape mRect;
};