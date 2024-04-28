#ifndef TIMBER_H
#define TIMBER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <map>
#include <string>

using namespace std;
using namespace sf;

class ResourceManager {
public:
    static void loadTexture(const std::string& name, const std::string& filename);
//    static sf::Sprite loadSprite(const std::string& name, float posX, float posY);
    static sf::Sprite loadSprite(const std::string& name, float posX, float posY);
    static sf::Texture& getTexture(const std::string& name);

private:
    static std::map<std::string, sf::Texture> textures;
};

class Game {
public:
    Game();  // Constructor for setting up the game
    void run();  // Starts the main loop of the game

private:
    sf::RenderWindow window;  // Window for the game
    bool isPaused;

    void processEvents();  // Process user input and system events
    void update(float deltaTime);  // Update the state of the game
    void render();  // Render the game graphics

    // Add other game components as needed
    Player player;  // Assuming Player class is defined elsewhere in Timber.h
    // Other components like Clouds, Branches, etc.
};
/*
 * The Player class represents the player character in the game.
 * It is responsible for updating the player's position and handling input.
 */
class Player {
public:
    Player();
    void update(float deltaTime);  // Include deltaTime for movement calculations
    sf::Sprite& getSprite();
    void handleInput(sf::Keyboard::Key key, bool isPressed);

private:
    sf::Sprite sprite;
    bool movingLeft;
    bool movingRight;
    float speed = 100.0f;  // Speed at which the player moves
};

class Tree {
public:
    Tree(const string &textureFile);

    Sprite &getSprite();

private:
    Texture texture;
    Sprite sprite;
};

class Cloud {
public:
    Cloud(const string &textureFile, bool active, float speed);
    void update(float deltaTime);
    void draw(RenderWindow& window);
    void setPosition(float x, float y);
    bool isActive() const;
    void setActive(bool active);

private:
    Texture texture;
    Sprite sprite;
    bool active;
    float speed;
};

class Branch {
public:
    enum class Side { LEFT, RIGHT, NONE };

    explicit Branch(const string &textureFile);
    void setPosition(float x, float y);
    void setSide(Side side);
    Sprite &getSprite();

private:
    Sprite sprite;
    Side branchSide;
};


class Background{
public:
    Background(const string &textureFile);
    void draw(RenderWindow &window);

private:
    Texture textureBackground;
    Sprite spriteBackground;
    Sprite sprite;

};

class HUD{
public:
    HUD();
    void updateScore(int score);
    void updateTime(int time);
    void draw(RenderWindow &window);

private:
    Font font;
    Text scoreText;
    Text timeText;
};

#endif
