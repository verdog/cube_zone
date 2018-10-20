#include "cube.hpp"

Cube::Cube(CubeZoneGame *game) 
: DrawableGameObject(game)
{
    mRect.setSize(sf::Vector2f(16, 16));
    mRect.setFillColor(sf::Color::White);

    srand(time(nullptr));

    mX = rand() % 50;
    mY = rand() % 25;

    mColor = sf::Color(
        rand() % 256,
        rand() % 256,
        rand() % 256
    );
    mRect.setFillColor(mColor);

    mVelocity = sf::Vector2f(0, 0);
}

Cube::~Cube() {

}

void Cube::move(int x, int y) {
    mX = (mX + x) % 50;
    mY = (mY + y) % 25;
    
    while (mX < 0) {
        mX += 50;
    }

    while (mY < 0) {
        mY += 25;
    }

    mVelocity = sf::Vector2f(x, y);
}

void Cube::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(mRect);
}

void Cube::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        move(0, -1);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        move(-1, 0);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        move(0, 1);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        move(1, 0);
    }

    if (
        !sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::D)
    ) {
        mVelocity = sf::Vector2f(0, 0);
    }
}

void Cube::update() {
    mRect.setPosition(sf::Vector2f(mX * 16, mY * 16));
    if (mVelocity.x != 0) {
        mRect.setOrigin(0, -8);
        mRect.setScale(1, 0.50);
    } else if (mVelocity.y != 0) {
        mRect.setOrigin(-8, 0);
        mRect.setScale(0.50, 1);
    } else {
        mRect.setOrigin(0, 0);
        mRect.setScale(1, 1);
    }
}
