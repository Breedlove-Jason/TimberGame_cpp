#ifndef LOADRESOURCES_H
#define LOADRESOURCES_H

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class LoadResources {
public:
    LoadResources(RenderWindow& window, const string& textureName, const string& spriteName, const string& filename, int positionX, int positionY, const Vector2f& direction, float speed);

    void setTextureName(const string& textureName);
    void draw();
    void move(float dt); // Add this method to move the sprite

    bool isActive() const; // Getter for beeActive
    void setActive(bool active); // Setter for beeActive

    float getSpeed() const; // Getter for beeSpeed
    void setSpeed(float speed); // Setter for beeSpeed

    Vector2f getDirection() const; // Getter for direction
    void setDirection(float x, float y); // Setter for direction

    Sprite& getSprite();

private:
    void createSprite();
    void loadTexture();

    string textureName;
    string spriteName;
    string filename;
    int positionX;
    int positionY;
    Texture texture;
    Sprite sprite;
    RenderWindow& window;

    bool beeActive; // Add this variable
    float beeSpeed; // Add this variable
    Vector2f direction; // Add this variable
};

#endif //LOADRESOURCES_H
