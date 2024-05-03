#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "../Managers/ResourceManager.h"

using namespace std;
using namespace sf;

class Player {
public:
    Player();

    // Updates the player's position based on current movement states.
    void update(float deltaTime);

    // Handles keyboard input to update movement states.
    void handleInput(Keyboard::Key key, bool isPressed);

    // Returns the player's sprite for rendering.
    const Sprite& getSprite() const;

    void draw(sf::RenderWindow& window) const;
private:
    Sprite sprite;
    bool movingLeft = false;
    bool movingRight = false;
    float speed = 200.0f;  // Speed at which the player moves in pixels per second.
};

#endif // PLAYER_H