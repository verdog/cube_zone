#include "game.hpp"
#include "gameobject.hpp"
#include "cube.hpp"

using CZG = CubeZoneGame;

CZG::CubeZoneGame() 
: mRenderWindow(sf::VideoMode(1600, 800), "cube_zone")
{
    mRenderTexture.create(800, 400);
}

CZG::~CubeZoneGame() {

}

bool CZG::init() {
    mTex.setTexture(mRenderTexture.getTexture());
    mTex.scale(sf::Vector2f(2.0, 2.0));

    mRenderWindow.setVerticalSyncEnabled(60);
    
    addGameObject(new Cube(this));
}

bool CZG::run() {
    // The main loop - ends as soon as the mRenderWindow is closed
    while (mRenderWindow.isOpen()) {
        // Event processing
        sf::Event event;
        while (mRenderWindow.pollEvent(event))
        {
            // Request for closing the mRenderWindow
            if (event.type == sf::Event::Closed)
                mRenderWindow.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    mRenderWindow.close();
                }
            }
        }
        // Clear the whole mRenderWindow before rendering a new frame
        mRenderWindow.clear(sf::Color::Magenta);
        mRenderTexture.clear(sf::Color::Black);

        for (auto Obj : mDrawableGameObjects) {
            mRenderTexture.draw(*Obj);
        }

        // End the current frame and display its contents on screen
        mRenderTexture.display();

        mRenderWindow.draw(mTex);

        mRenderWindow.display();
    }
}

bool CZG::addGameObject(GameObject* obj) {
    auto ptr = std::shared_ptr<GameObject>(obj);
    mGameObjects.push_back(ptr);

    auto drawable = std::dynamic_pointer_cast<DrawableGameObject>(ptr);

    if (drawable != nullptr) {
        mDrawableGameObjects.push_back(drawable);
    }
}