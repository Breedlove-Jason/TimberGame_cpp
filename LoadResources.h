#ifndef LOADRESOURCES_H
#define LOADRESOURCES_H

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class LoadResources {
public:
    LoadResources(RenderWindow& window, const string& textureName, const string& spriteName, const string& filename, int positionX, int positionY);

    void setTextureName(const string& textureName);
    void draw();

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
};

#endif //LOADRESOURCES_H
