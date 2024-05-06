#include "LoadResources.h"

LoadResources::LoadResources(RenderWindow& window, const string& textureName, const string& spriteName, const string& filename, const int positionX, const int positionY, const Vector2f& direction, float speed)
: window(window), beeActive(false), beeSpeed(speed), direction(direction) {
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

Sprite& LoadResources::getSprite() {
    return sprite;
}

void LoadResources::draw() {
    window.draw(sprite);
}

void LoadResources::move(float dt) {
    if (beeActive) {
        sprite.setPosition(sprite.getPosition() + direction * beeSpeed * dt);
        if (sprite.getPosition().x < -100) {
            sprite.setPosition(2000, sprite.getPosition().y); // Set the sprite's position to the right side of the screen
        }
    }
}

bool LoadResources::isActive() const {
    return beeActive;
}

void LoadResources::setActive(bool active) {
    beeActive = active;
}

float LoadResources::getSpeed() const {
    return beeSpeed;
}

void LoadResources::setSpeed(float speed) {
    beeSpeed = speed;
}

Vector2f LoadResources::getDirection() const {
    return direction;
}

void LoadResources::setDirection(float x, float y) {
    direction.x = x;
    direction.y = y;
}