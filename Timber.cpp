#include "Timber.h"
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

using namespace sf;
using namespace std;

Game::Game() : window(sf::VideoMode(1920, 1080), "Timber!!!"), isPaused(true) {
    // Initialization code here (load textures, set up scenes, etc.)
}

std::map<std::string, sf::Texture> ResourceManager::textures;

void ResourceManager::loadTexture(const std::string &name, const std::string &filename) {
    sf::Texture &tex = textures[name];
    if (tex.getSize().x == 0) { // Check if texture is already loaded
        if (!tex.loadFromFile(filename)) {
            throw std::runtime_error("Failed to load texture: " + filename);
        }
    }
}

sf::Sprite ResourceManager::loadSprite(const std::string &name, float posX, float posY) {
    sf::Texture &texture = getTexture(name);
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(posX, posY);
    return sprite;
}

sf::Texture &ResourceManager::getTexture(const std::string &name) {
    return textures.at(name);
}

Game::Game()
        : window(sf::VideoMode(1920, 1080), "Timber!!!"), isPaused(true) {
    // Load all necessary resources
    ResourceManager::loadTexture("player", "graphics/player.png");
    ResourceManager::loadSprite("player", 580, 720);
    // Initialize other game components here
    player = Player();  // Assuming player setup uses ResourceManager
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        processEvents();
        if (!isPaused) {
            update(deltaTime.asSeconds());
        }
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
                // Handle other events like keyboard input
            case sf::Event::KeyPressed:
            case sf::Event::KeyReleased:
                player.handleInput(event.key.code, event.type == sf::Event::KeyPressed);
                break;
        }
    }
}

void Game::update(float deltaTime) {
    if (!isPaused) {
        player.update(deltaTime);  // Update player's state
        // Update other components like clouds, branches
    }
}

void Game::render() {
    window.clear();
    window.draw(player.getSprite());  // Draw the player
    // Draw other components
    window.display();
}

Player::Player() {
    sprite = ResourceManager::loadSprite("graphics/player.png", 580, 720);
}

void Player::update(float deltaTime) {
    if (movingLeft) {
        sprite.move(-speed * deltaTime, 0);
    }
    if (movingRight) {
        sprite.move(speed * deltaTime, 0);
    }
}

sf::Sprite &Player::getSprite() {
    return sprite;
}

void Player::handleInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::Left) {
        movingLeft = isPressed;
    } else if (key == sf::Keyboard::Right) {
        movingRight = isPressed;
    }
}

Tree::Tree(const string &) {
    sprite = ResourceManager::loadSprite("graphics/tree.png", 810, 0);

}

Sprite &Tree::getSprite() {
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

void Cloud::draw(RenderWindow &window) {
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


Branch::Branch(const string &) {
    sprite = ResourceManager::loadSprite("graphics/branch.png", 220, 20);
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

Sprite &Branch::getSprite() {
    return sprite;
}

Background::Background(const string &textureFile) {
    sprite = ResourceManager::loadSprite(textureFile, 0, 0);
}

void Background::draw(RenderWindow &window) {
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

void HUD::draw(RenderWindow &window) {
    window.draw(scoreText);
    window.draw(timeText);
}

void HUD::updateTime(int time) {

}
