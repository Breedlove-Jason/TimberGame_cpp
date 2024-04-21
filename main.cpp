#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <filesystem>

#include "Timber.h"

using namespace sf;
namespace fs = std::filesystem;
using namespace std;

int main() {
        fs::path pathToImage = fs::current_path() / "graphics/background.png";
        std::cout << "Full path to image: " << pathToImage << std::endl;

        std::ifstream file(pathToImage);
        if (file.good()) {
            std::cout << "File exists" << std::endl;
        } else {
            std::cout << "File does not exist" << std::endl;
        }
        // Continue with the rest of your main function...
    // create a video mode object
    VideoMode vm(1920, 1080);

    // create and open a window for the game
    RenderWindow window(vm, "Timber!!!"); // set style to fullscreen when ready

    // create a texture to hold a graphic on the GPU
    Texture textureBackground;

    // load a graphic into the texture
    textureBackground.loadFromFile("graphics/background.png");


// the rest of your code...
    // create a sprite
    Sprite spriteBackground;

    // attach the texture to the sprite
    spriteBackground.setTexture(textureBackground);

    // set the spriteBackground to cover the screen
    spriteBackground.setPosition(0, 0);

    while (window.isOpen()) {
        /*
         * ****************************************************
         * Handle the player input
         * ****************************************************
         */
        if(Keyboard::isKeyPressed((Keyboard::Escape))) {
            window.close();
        }

        /*
         * ****************************************************
         * Update the scene
         * ****************************************************
         */



        /*
         * ****************************************************
         * Draw the scene
         * ****************************************************
         */

        // clear screen
        window.clear();

        // draw game scene here
        window.draw(spriteBackground);

        // show everything we just drew
        window.display();

    }

    return 0;
}