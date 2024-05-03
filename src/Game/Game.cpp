#include "Game.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Entities/Player.h"

using namespace std;
using namespace sf;

Game::Game()
    : window(sf::VideoMode(1920, 1080), "Timber!!!"), isPaused(true),
      background("background", 0, 0), tree("tree", 810, 0){
    // Initialize game components
    trees.emplace_back("mainTree", 810, 0);
    trees.emplace_back("extraTree1", 300, -125);
    trees.emplace_back("extraTree2", 1400, -200);
    clouds.emplace_back("cloud", 0, 250, true, 0.5f);
    branches.emplace_back("branch", 220, 20);

    // Load all necessary resources
    ResourceManager::loadTexture("background", "graphics/background.png");
    ResourceManager::loadTexture("player", "graphics/player.png");
    ResourceManager::loadTexture("tree", "graphics/tree.png");
    ResourceManager::loadTexture("cloud", "graphics/cloud.png");
    ResourceManager::loadTexture("branch", "graphics/branch.png");

    // Setup HUD
    hud = HUD();
}

void Game::run() {
    Clock clock;
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        processEvents();
        if (!isPaused) {
            update(deltaTime);
        }
        render();
    }
}

void Game::processEvents() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            window.close();
        // More event handling can be implemented here
    }
}

void Game::update(Time deltaTime) {
    float dt = deltaTime.asSeconds();
    player.update(dt);
    for (auto& cloud : clouds) {
        cloud.update(dt);
    }
    for (auto& branch : branches) {
        // Assume branches have an update method
        // branch.update(dt);
    }
    checkCollisions();
    handleGameLogic();
}

void Game::checkCollisions() {
    // Example: Check if the player collides with any branches
    for (auto& branch : branches) {
        if (branch.getSide() != Branch::Side::NONE) { // Assuming branch is visible and not off-screen
            // Check collision only if the branch is visible and has a side set
            sf::FloatRect playerBounds = player.getSprite().getGlobalBounds();
            sf::FloatRect branchBounds = branch.getSprite().getGlobalBounds();

            // Simple AABB collision detection
            if (playerBounds.intersects(branchBounds)) {
                // Handle the collision
                handlePlayerBranchCollision(branch);
            }
        }
    }

    // Further collision checks can be added here
    // For example, checking for collisions with power-ups, enemies, or obstacles
}

void Game::handlePlayerBranchCollision(Branch& branch) {
    // Logic to handle what happens when a player collides with a branch
    // This could involve resetting the player's position, reducing player's health, or triggering a game over

    // Example: Trigger a game over or restart the scenario
    isPaused = true; // Pause the game
    std::cout << "Player has collided with a branch! Game Over." << std::endl;

    // Reset the game state or branch state if needed
    branch.setSide(Branch::Side::NONE); // Optionally reset the branch position

    // Additional actions such as updating the HUD can be performed here
    hud.updateScore(player.getScore() - 50); // Assuming player has a score method
    hud.updateTime(0); // Reset the time or reduce it as a penalty
}


void Game::handleGameLogic() {
    // Example: Check if the game timer has run out
    if (hud.getTimeRemaining() <= 0) {
        isPaused = true; // Pause the game
        std::cout << "Time's up! Game Over." << std::endl;
        // You could call a method here to display a game over screen or menu
        displayGameOverScreen();
    }

    // Example: Check for win condition
    if (player.getScore() >= 1000) {
        isPaused = true; // Pause the game to celebrate the win
        std::cout << "Congratulations! You've won the game!" << std::endl;
        // You could call a method here to display a victory screen
        displayVictoryScreen();
    }

    // Update HUD with current game state
    hud.updateScore(player.getScore());
    hud.updateTime(hud.getTimeRemaining() - 1); // Decrease time remaining by 1 each call, adjust as needed

    // Additional logic based on player health or game conditions
    if (player.getHealth() <= 0) {
        isPaused = true;
        std::cout << "Player health depleted. Game Over." << std::endl;
        // Reset the game or provide options to restart
        displayGameOverScreen();
    }
}

void Game::render() {
    window.clear();
    background.draw(window);
    for (const auto& tree : trees) {
        window.draw(tree.getSprite());
    }
    for (const auto& cloud : clouds) {
        cloud.draw(window);
    }
    for (const auto& branch : branches) {
        window.draw(branch.getSprite());
    }
    window.draw(player.getSprite());
    hud.draw(window);
    window.display();
}
