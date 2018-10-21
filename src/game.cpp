#include "game.hpp"
#include "gameobject.hpp"
#include "remoteserver.hpp"
#include "cube.hpp"

using CZG = CubeZoneGame;

CZG::CubeZoneGame() 
: mRenderWindow(sf::VideoMode(800, 400), "cube_zone")
, mRemoteServer("localhost", 3001)
{
    mRenderTexture.create(800, 400);
}

CZG::~CubeZoneGame() {

}

bool CZG::init() {
    mTex.setTexture(mRenderTexture.getTexture());
    // mTex.scale(sf::Vector2f(2.0, 2.0));

    mRenderWindow.setVerticalSyncEnabled(60);
    
    Cube* cube = (new Cube(this));
    addGameObject(cube);
    mRemoteServer.setCube(cube);
    mRemoteServer.setMap(&mNetworkCubes);
}

bool CZG::run() {
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

                if (event.key.code == sf::Keyboard::R) {
                    mRemoteServer.connect();
                }
            }
        }

        if (!mRenderWindow.hasFocus()) {
            continue;
        }

        for (auto Obj : mGameObjects) {
            Obj->handleInput();
            Obj->update();
        }

        // Clear the whole mRenderWindow before rendering a new frame
        mRenderWindow.clear(sf::Color::Magenta);
        mRenderTexture.clear(sf::Color::Black);

        for (auto Obj : mDrawableGameObjects) {
            mRenderTexture.draw(*Obj);
        }

        for (auto pair : mNetworkCubes) {
            Cube& cube = *(pair.second);

            cube.update();
            mRenderTexture.draw(cube);
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