#include "Tree.h"

using namespace std;
using namespace sf;

Tree::Tree(const string &textureName, float posX, float posY) {
    // Load the sprite using the ResourceManager with specified position
    sprite = ResourceManager::loadSprite(textureName, posX, posY);
}

const Sprite& Tree::getSprite() const {
    return sprite;
}