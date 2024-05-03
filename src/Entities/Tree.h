
#ifndef TREE_H
#define TREE_H

#include <SFML/Graphics.hpp>
#include "../Managers/ResourceManager.h"

using namespace std;
using namespace sf;

class Tree {
public:
    Tree(const string &textureName, float posX, float posY);

    // Returns the tree's sprite for rendering.
    const Sprite& getSprite() const;

private:
    Sprite sprite;
};

#endif // TREE_H
