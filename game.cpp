#include "game.hpp"
#include "gameobject.hpp"
#include "cube.hpp"

using CZG = CubeZoneGame;

CZG::CubeZoneGame() 
: mRenderwindow(sf::VideoMode(1600, 800), "cube_zone")
{

}

CZG::~CubeZoneGame() {

}

bool CZG::init() {
    mRenderwindow.setVerticalSyncEnabled(60);

    addGameObject(new Cube(this));
}

bool CZG::run() {
    // The main loop - ends as soon as the mRenderwindow is closed
    while (mRenderwindow.isOpen()) {
        // Event processing
        sf::Event event;
        while (mRenderwindow.pollEvent(event))
        {
            // Request for closing the mRenderwindow
            if (event.type == sf::Event::Closed)
                mRenderwindow.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    mRenderwindow.close();
                }
            }
        }
        // Clear the whole mRenderwindow before rendering a new frame
        mRenderwindow.clear(sf::Color::Black);

        for (auto Obj : mDrawableGameObjects) {
            mRenderwindow.draw(*Obj);
        }

        // End the current frame and display its contents on screen
        mRenderwindow.display();
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