#ifndef BRANCH_H
#define BRANCH_H

#include <SFML/Graphics.hpp>
#include "../Managers/ResourceManager.h"

using namespace std;
using namespace sf;

class Branch {
public:
    // Enumeration to specify the side of the tree that a branch is on
    enum class Side { LEFT, RIGHT, NONE };

    Branch(const string &textureName, float posX, float posY);

    // Sets the position of the branch and adjusts based on the side
    void setPosition(float x, float y);

    // Sets the side of the tree the branch is on
    void setSide(Side side);

    // Returns the branch's sprite for rendering
    const Sprite& getSprite() const;

private:
    Sprite sprite;
    Side branchSide = Side::NONE;
};

#endif // BRANCH_H

