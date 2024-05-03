#include "Cloud.h"
#include "../Managers/ResourceManager.h"

using namespace std;
using namespace sf;



Cloud::Cloud(const string &textureName, float posX, float posY, bool active, float speed)
    : active(active), speed(speed) {
    // Load the sprite using the ResourceManager with specified position
    sprite = ResourceManager::loadSprite(textureName, posX, posY);
}

void Cloud::update(float deltaTime) {
    if (active) {
        // Move the cloud across the screen at the given speed
        sprite.move(speed * deltaTime, 0);

        // Check if the cloud has moved past the screen bounds and reset or deactivate it as necessary
        if (sprite.getPosition().x > 1920 + sprite.getLocalBounds().width || sprite.getPosition().x < -sprite.getLocalBounds().width) {
            active = false; // Deactivate the cloud
        }
    }
}

void Cloud::draw(sf::RenderWindow &window) const{
    if (active) {
        window.draw(sprite);
    }
}

void Cloud::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

bool Cloud::isActive() const {
    return active;
}

void Cloud::setActive(bool active) {
    this->active = active;
}

