#include "cube.hpp"

Cube::Cube(CubeZoneGame *game) 
: DrawableGameObject(game)
{
    mRect.setSize(sf::Vector2f(16, 16));
    mRect.setFillColor(sf::Color::White);
}

Cube::~Cube() {

}

void Cube::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(mRect);
}