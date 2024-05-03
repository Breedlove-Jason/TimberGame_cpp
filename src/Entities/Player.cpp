#include "Player.h"

using namespace sf;

Player::Player() {
    // Assume "player" is the key for the player's texture in the ResourceManager.
    sprite = ResourceManager::loadSprite("player", 580, 720);
}

void Player::update(float deltaTime) {
    // Update player position based on movement flags
    if (movingLeft) sprite.move(-speed * deltaTime, 0);
    if (movingRight) sprite.move(speed * deltaTime, 0);
}

void Player::handleInput(Keyboard::Key key, bool isPressed) {
    // Determine which key is pressed and update movement direction
    switch (key) {
        case Keyboard::Left:
            movingLeft = isPressed;
        break;
        case Keyboard::Right:
            movingRight = isPressed;
        break;
        default:
            // Handle other keys if necessary
                break;
    }
}

const Sprite& Player::getSprite() const{
    return sprite;
}

void Player::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

