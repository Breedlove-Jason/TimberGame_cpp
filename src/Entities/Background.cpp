#include "Background.h"
#include "../Managers/ResourceManager.h"

using namespace std;
using namespace sf;

Background::Background(const string &textureName, float posX, float posY) {
    // Load the sprite using the ResourceManager with specified position
    sprite = ResourceManager::loadSprite(textureName, posX, posY);
}

void Background::draw(RenderWindow &window) {
    window.draw(sprite);
}

