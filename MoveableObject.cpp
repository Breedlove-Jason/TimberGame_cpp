#include "MoveableObject.h"
#include "LoadResources.h"
#include <iostream>
#include <string>

using namespace std;
MovableObject::MovableObject(RenderWindow& window, const string& textureName, const string& spriteName, const string& filename, int positionX, int positionY, const Vector2f& direction, float speed)
: LoadResources(window, textureName, spriteName, filename, positionX, positionY, direction, speed) {}

void MovableObject::moveObject(float dt, int speedRange, int heightRange, int seedFactor) {
    if (!isActive()) {
        setSpeed((rand() % speedRange) + 200);
        float height = (rand() % heightRange) + 500;
        setDirection(-1.0f, 0.0f);
        setActive(true);
    }
    else {
        move(dt);
        if (getSprite().getPosition().x < -100) {
            setActive(false);
        }
    }
}