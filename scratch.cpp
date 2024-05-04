#include "Timber.h"

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
