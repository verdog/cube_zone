#include "game.hpp"
#include "gameobject.hpp"
#include "remoteserver.hpp"
#include "cube.hpp"

using CZG = CubeZoneGame;

CZG::CubeZoneGame() 
: mRenderWindow(sf::VideoMode(128 * 4, 128 * 4), "cube_zone")
, mRemoteServer("localhost", 3001)
{
    mRenderTexture.create(128, 128);
}

CZG::~CubeZoneGame() {

}

bool CZG::init() {
    mTex.setTexture(mRenderTexture.getTexture());
    mTex.scale(sf::Vector2f(4.0, 4.0));

    mRenderWindow.setVerticalSyncEnabled(60);
    
    Cube* cube = (new Cube(this));
    addGameObject(cube);
    mRemoteServer.setCube(cube);
    mRemoteServer.setMap(&mNetworkCubes);
}

bool CZG::run() {
    float tTime, dTime;
    dTime = tTime = 0;
    
    sf::Clock clock;

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

        // update dtime
        tTime += clock.getElapsedTime().asSeconds();
        dTime += clock.getElapsedTime().asSeconds();
        clock.restart();

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

        // update network?
        if (mRemoteServer.isConnected() && dTime > 1/10.f) {
            std::cout << "Tick at " << tTime << std::endl;
            mRemoteServer.tick();
            dTime = 0;
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