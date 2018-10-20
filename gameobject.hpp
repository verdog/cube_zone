#pragma once

#include <SFML/Graphics.hpp>

class CubeZoneGame;

class GameObject {
    public:
        GameObject(CubeZoneGame *game);
        virtual ~GameObject();

        CubeZoneGame* getGame();
    private:
        CubeZoneGame* mGame;
};

class DrawableGameObject : public GameObject, public sf::Drawable {
    public:
        DrawableGameObject(CubeZoneGame *game);
        virtual ~DrawableGameObject();

        void draw(sf::RenderWindow&, sf::RenderStates) const;
    private:
};