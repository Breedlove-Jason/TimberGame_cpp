#ifndef MOVABLEOBJECT_H
#define MOVABLEOBJECT_H

#include "LoadResources.h"

class MovableObject : public LoadResources {
public:
    MovableObject(RenderWindow& window, const string& textureName, const string& spriteName, const string& filename, int positionX, int positionY, const Vector2f& direction, float speed);

    void moveObject(float dt, int speedRange, int heightRange, int seedFactor);
};

#endif //MOVABLEOBJECT_H
