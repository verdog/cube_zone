#include "game.hpp"
#include "gameobject.hpp"

GameObject::GameObject(CubeZoneGame *game) 
: mGame {game}
{

}

DrawableGameObject::DrawableGameObject(CubeZoneGame *game)
: GameObject(game)
{}

GameObject::~GameObject() {

}

DrawableGameObject::~DrawableGameObject() = default;

CubeZoneGame* GameObject::getGame() {
    return mGame;
}