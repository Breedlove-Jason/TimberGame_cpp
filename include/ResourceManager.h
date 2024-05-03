#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class ResourceManager {
public:
    static void loadTexture(const std::string& name, const std::string& filename);
    static sf::Sprite loadSprite(const std::string& name, float posX, float posY);
    static sf::Texture& getTexture(const std::string& name);

private:
    static std::map<std::string, sf::Texture> textures;
};

#endif // RESOURCE_MANAGER_H

