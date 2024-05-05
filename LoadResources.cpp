#include "LoadResources.h"

LoadResources::LoadResources(RenderWindow&window, const string&textureName, const string&spriteName,
                             const string&filename, const int positionX, const int positionY)
    : window(window), active(false), speed(0.0f), direction(0.0f, 0.0f) {
    // Initialize active, speed and direction here
    this->textureName = textureName;
    this->spriteName = spriteName;
    this->filename = filename;
    this->positionX = positionX;
    this->positionY = positionY;
    loadTexture();
    createSprite();
}

void LoadResources::setTextureName(const string&textureName) {
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

Sprite& LoadResources::getSprite() {
    return sprite;
}

bool LoadResources::isActive() const {
    return active;
}

void LoadResources::setActive(bool active) {
    this->active = active;
}

float LoadResources::getSpeed() const {
    return speed;
}

void LoadResources::setSpeed(float speed) {
    this->speed = speed;
}

void LoadResources::setDirection(float dx, float dy) {
    direction.x = dx;
    direction.y = dy;
}

void LoadResources::move(float dt) {
    if (active) {
        sprite.setPosition(sprite.getPosition() + direction * speed * dt);
        if (sprite.getPosition().x < -100) {
            sprite.setPosition(2000, sprite.getPosition().y);
            // Set the sprite's position to the right side of the screen
        }
    }
}
