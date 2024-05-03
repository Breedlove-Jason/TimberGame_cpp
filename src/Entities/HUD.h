#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>
#include "../Managers/ResourceManager.h"

using namespace sf;

class HUD {
public:
    HUD();

    // Updates the score display
    void updateScore(int score);

    // Updates the time display
    void updateTime(float time);

    // Draws the HUD elements on the provided render window
    void draw(sf::RenderWindow &window);

private:
    Font font;
    Text scoreText;
    Text timeText;
};

#endif // HUD_H