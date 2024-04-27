#include "Timber.h"
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

using namespace sf;
using namespace std;

Game::Game() : window(sf::VideoMode(1920, 1080), "Timber!!!"), isPaused(true) {
    // Initialization code here (load textures, set up scenes, etc.)
}

map<string, Texture> ResourceManager::textures;

Sprite ResourceManager::loadSprite(const string& textureFile, float posX, float posY) {
    auto& texture = textures[textureFile];
    if (texture.getSize().x == 0) { // Texture not yet loaded
        if (!texture.loadFromFile(textureFile)) {
            throw runtime_error("Failed to load texture: " + textureFile);
        }
    }

    Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(posX, posY);
    return sprite;
}

void Game::run() {
    Clock clock;
    while (window.isOpen()) {
        Time deltaTime = clock.restart();
        processEvents();
        if (!isPaused) {
            updates(); // might need update(deltaTime) instead
        }
        render();
    }
}
void Game::processEvents() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }
    }
}

void Game::updates() {
    // Update game state
}

void Game::render() {
    window.clear();
    // Draw everything
    window.display();
}


Player::Player() : movingLeft(false), movingRight(false) {
    sprite = ResourceManager::loadSprite("graphics/player.png", 580, 720);
}

void Player::update(float deltaTime) {
    // Use movingLeft and movingRight to update the sprite's position
    if (movingLeft) {
        sprite.move(-speed * deltaTime, 0);
    }
    if (movingRight) {
        sprite.move(speed * deltaTime, 0);
    }
}

Sprite& Player::getSprite() {
    return sprite;
}

void Player::handleInput(Keyboard::Key key, bool isPressed) {
    if (key == Keyboard::Left) {
        movingLeft = isPressed;
    } else if (key == Keyboard::Right) {
        movingRight = isPressed;
    }
}

Tree::Tree(const string&) {
    sprite = ResourceManager::loadSprite("graphics/tree.png", 810, 0);

}

Sprite& Tree::getSprite() {
    return sprite;
}

Cloud::Cloud(const string &textureFile, bool active, float speed)
        : active(active), speed(speed) {
    texture.loadFromFile(textureFile);
    sprite.setTexture(texture);
}

void Cloud::update(float deltaTime) {
    if (!active) return;

    // Move the cloud across the screen
    float movement = speed * deltaTime;
    sprite.move(movement, 0);

    // Check if the cloud has moved past the screen bounds
    if (sprite.getPosition().x > 1920 || sprite.getPosition().x < -sprite.getLocalBounds().width) {
        active = false; // Deactivate the cloud
    }
}

void Cloud::draw(RenderWindow& window) {
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


Branch::Branch(const string&) {
    sprite= ResourceManager::loadSprite("graphics/branch.png", 220, 20);
    branchSide = Side::NONE; // Default to NONE.
}

void Branch::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void Branch::setSide(Side side) {
    branchSide = side;
    switch (side) {
        case Side::LEFT:
            sprite.setRotation(180);
            sprite.setPosition(sprite.getPosition().x + sprite.getGlobalBounds().width, sprite.getPosition().y);
            break;
        case Side::RIGHT:
            sprite.setRotation(0);
            break;
        case Side::NONE:
            sprite.setPosition(-1000, -1000); // Hide off-screen
            break;
    }
}

Sprite& Branch::getSprite() {
    return sprite;
}
Background::Background(const string& textureFile) {
    sprite = ResourceManager::loadSprite(textureFile, 0, 0);
}

void Background::draw(RenderWindow& window) {
    window.draw(sprite);
}

HUD::HUD() {
    font.loadFromFile("fonts/KOMIKAP_.ttf");
    scoreText.setFont(font);
    timeText.setFont(font);
}

void HUD::updateScore(int score) {
    scoreText.setString("Score: " + to_string(score));
}

void HUD::updateTime(float time) {
    timeText.setString("Time: " + to_string(time));
}

void HUD::draw(RenderWindow& window) {
    window.draw(scoreText);
    window.draw(timeText);
}

void HUD::updateTime(int time) {

}
