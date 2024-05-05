#include "LoadResources.h"

LoadResources::LoadResources(RenderWindow& window, const string& textureName, const string& spriteName, const string& filename, const int positionX, const int positionY)
: window(window) {
    this->textureName = textureName;
    this->spriteName = spriteName;
    this->filename = filename;
    this->positionX = positionX;
    this->positionY = positionY;
    loadTexture();
    createSprite();
}

void LoadResources::setTextureName(const string& textureName) {
    this->textureName = textureName;
}

void LoadResources::loadTexture() {
    if (!texture.loadFromFile(filename)) {
        throw std::runtime_error("Failed to load texture: " + filename);
    }
}

void LoadResources::createSprite() {
    sprite.setTexture(texture);
    sprite.setPosition(positionX, positionY);
}

void LoadResources::draw() {
    window.draw(sprite);
}