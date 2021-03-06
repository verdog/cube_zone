#include "cube.hpp"
#include "game.hpp"

Cube::Cube(CubeZoneGame *game) 
: DrawableGameObject(game)
{
    mRect.setSize(sf::Vector2f(16, 16));
    mRect.setFillColor(sf::Color::White);

    srand(time(nullptr));

    mX = rand() % 8;
    mY = rand() % 8;

    mColor = sf::Color(
        rand() % 256,
        rand() % 256,
        rand() % 256
    );
    mRect.setFillColor(mColor);

    mVelocity = sf::Vector2f(0, 0);

    keyDown = false;

    resetTimeToLive();
}

Cube::~Cube() {

}

void Cube::resetTimeToLive() {
    mTimeToLive = 3;
}

void Cube::decrementTimeToLive() {
    mTimeToLive--;
}

int Cube::getTimeToLive() {
    return mTimeToLive;
}

void Cube::move(int x, int y) {
    mX = (mX + x) % 8;
    mY = (mY + y) % 8;
    
    while (mX < 0) {
        mX += 8;
    }

    while (mY < 0) {
        mY += 8;
    }

    mVelocity = sf::Vector2f(x, y);
}

void Cube::setPosition(int x, int y) {
    mX = (x) % 8;
    mY = (y) % 8;

    while (mX < 0) {
        mX += 8;
    }

    while (mY < 0) {
        mY += 8;
    }
}

sf::Vector2i Cube::getPosition() {
    return sf::Vector2i(mX, mY);
}

void Cube::setColor(sf::Color c) {
    mRect.setFillColor(c);
    mColor = c;
}

sf::Color Cube::getColor() {
    return mColor;
}

void Cube::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(mRect);
}

void Cube::handleInput() {
    if (!keyDown && mGame->mRenderWindow.hasFocus()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            move(0, -1);
            keyDown = true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            move(-1, 0);
            keyDown = true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            move(0, 1);
            keyDown = true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            move(1, 0);
            keyDown = true;
        }
    }

    if (
        !sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::D)
    ) {
        mVelocity = sf::Vector2f(0, 0);
        keyDown = false;
    }
}

void Cube::update() {
    mRect.setPosition(sf::Vector2f(mX * 16, mY * 16));
}
