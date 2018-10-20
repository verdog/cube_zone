#include "game.hpp"

using CZG = CubeZoneGame;

CZG::CubeZoneGame() 
: mRenderwindow(sf::VideoMode(800, 600), "cube_zone")
{

}

CZG::~CubeZoneGame() {

}

bool CZG::init() {
    mRenderwindow.setVerticalSyncEnabled(60);

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
        mRenderwindow.clear(sf::Color::Red);
        // End the current frame and display its contents on screen
        mRenderwindow.display();
    }
}