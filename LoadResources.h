#ifndef LOADRESOURCES_H
#define LOADRESOURCES_H

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class LoadResources {
public:
    LoadResources(RenderWindow&window, const string&textureName, const string&spriteName, const string&filename,
                  int positionX, int positionY);

    void setTextureName(const string&textureName);

    Sprite& getSprite();

    void draw();

    void move(float dt); // Modify this method to move the sprite based on direction and speed

    bool isActive() const; // Getter for active
    void setActive(bool active); // Setter for active

    float getSpeed() const; // Getter for speed
    void setSpeed(float speed); // Setter for speed

    void setDirection(float dx, float dy); // Add this method to set the direction of movement

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
    RenderWindow&window;

    bool active; // Rename this variable to 'active' to make it more generic
    float speed; // Rename this variable to 'speed' to make it more generic
    Vector2f direction; // Add this variable to store the direction of movement
};

#endif //LOADRESOURCES_H
