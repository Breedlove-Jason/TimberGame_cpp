#include "ResourceManager.h"

using namespace std;
using namespace sf;

map<string, Texture> ResourceManager::textures;

void ResourceManager::loadTexture(const string& name, const string& filename) {
    // Check if texture is already loaded
    auto tex = textures.find(name);
    if (tex == textures.end()) {
        sf::Texture texture;
        if (!texture.loadFromFile(filename)) {
            throw std::runtime_error("Failed to load texture: " + filename);
        }
        textures[name] = move(texture);
    }
}

Sprite ResourceManager::loadSprite(const string& name, float posX, float posY) {
    Sprite sprite;
    sprite.setTexture(getTexture(name));
    sprite.setPosition(posX, posY);
    return sprite;
}

Texture& ResourceManager::getTexture(const string& name) {
    auto tex = textures.find(name);
    if (tex != textures.end()) {
        return tex->second;
    }
    throw runtime_error("Texture not found: " + name);
}

void ResourceManager::clearResources() {
    textures.clear();
}