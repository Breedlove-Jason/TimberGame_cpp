#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <stdexcept>

using namespace sf;
using namespace std;

class ResourceManager {
public:
    // Loads a texture from file and stores it with a unique name.
    static void loadTexture(const string& name, const string& filename);

    // Retrieves a sprite object created from a previously loaded texture.
    static Sprite loadSprite(const string& name, float posX, float posY);

    // Returns a reference to the texture object associated with a given name.
    static Texture& getTexture(const string& name);

    // Clears all loaded textures from memory.
    static void clearResources();

private:
    static map<string, Texture> textures;
};

#endif // RESOURCE_MANAGER_H

