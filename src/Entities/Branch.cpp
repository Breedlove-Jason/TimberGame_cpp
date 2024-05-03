#include "Branch.h"
#include "../Managers/ResourceManager.h"

using namespace std;
using namespace sf;

Branch::Branch(const string&textureName, float posX, float posY) {
    sprite = ResourceManager::loadSprite(textureName, posX, posY);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
}

void Branch::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void Branch::setSide(Side side) {
    branchSide = side;
    switch (side) {
        case Side::LEFT:
            sprite.setRotation(180);
            sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y);
            break;
        case Side::RIGHT:
            sprite.setRotation(0);
            sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y);
            break;
        case Side::NONE:
            sprite.setPosition(-1000, -1000); // Position off-screen
            break;
    }
}

const Sprite& Branch::getSprite() const {
    return sprite;
}
