#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>
#include "../Managers/ResourceManager.h"

using namespace sf;
using namespace std;

class Background {
public:
    // Constructor that loads the background texture
    Background(const string &textureName, float posX, float posY);

    // Draw the background sprite on the provided render window
    void draw(RenderWindow &window);

private:
    Sprite sprite;
};

#endif // BACKGROUND_H
