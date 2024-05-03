#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
public:
    Player();

    void update(float deltaTime);
    void handleInput(sf::Keyboard::Key key, bool isPressed);
    sf::Sprite& getSprite();

private:
    sf::Sprite sprite;
    bool movingLeft = false;
    bool movingRight = false;
    float speed = 100.0f;  // Speed at which the player moves
};

#endif // PLAYER_H
