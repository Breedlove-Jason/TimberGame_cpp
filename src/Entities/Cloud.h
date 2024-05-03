#ifndef CLOUD_H
#define CLOUD_H

#include <SFML/Graphics.hpp>
#include "../Managers/ResourceManager.h"

using namespace std;
using namespace sf;

class Cloud {
public:
    Cloud(const string &textureName, float posX, float posY, bool active = false, float speed = 0.0f);

    // Updates the cloud's position based on its speed and activity.
    void update(float deltaTime);

    // Draws the cloud on the provided render window if it is active.
    void draw(RenderWindow &window) const;

    // Sets the position of the cloud.
    void setPosition(float x, float y);

    // Gets the cloud's activity state.
    bool isActive() const;

    // Sets the cloud's activity state.
    void setActive(bool active);

private:
    Sprite sprite;
    bool active;
    float speed; // Speed at which the cloud moves.
};

#endif // CLOUD_H

