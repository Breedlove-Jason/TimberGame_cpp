#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "ResourceManager.h" // Include ResourceManager

class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    bool isPaused;

    void processEvents();
    void update(float deltaTime);
    void render();

    // Game components
    sf::Sprite background;
    sf::Sprite mainTree;
    sf::Sprite player;
    std::vector<sf::Sprite> clouds; // To handle multiple clouds
    std::vector<sf::Sprite> branches; // To handle multiple branches
    sf::Sprite extraTree1;
    sf::Sprite extraTree2; // Additional trees
};

#endif // GAME_H
