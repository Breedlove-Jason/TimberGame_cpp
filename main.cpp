#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <cmath>
#include <cstdio>

#include "Timber.h"

using namespace sf;
namespace fs = std::filesystem;
using namespace std;

int main() {

        // What is the player's score?
        int playerScore = 0;

        // What is the player's first initial?
        char playerInitial = 'J';

        //What is the value of pi?
        const float valuePi = M_PI;

        // Is the player alive or dead
        bool isAlive = true;

        // get the random number and assign it to a variable
        int number = rand() % 100;


        // check graphics module is working
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
    RenderWindow window(vm, "Timber!!!"); // set style to fullscreen when ready Style::Fullscreen

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

    // make a tree sprite

    Texture textureTree;
    if (!textureTree.loadFromFile("graphics/tree.png")) {
        cout << "Can't load tree" << endl;
    }
    else {
        cout << "Tree loaded" << endl;

        textureTree.loadFromFile("graphics/tree.png");
    }
    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(810, 0);

    // prepare the bee
    Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");
    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0, 800);

    // Is the bee currently moving?
    bool beeActive = false;

    // How fast can the bee fly
    float beeSpeed = 0.0f;

    // prepare the clouds
    Texture textureCloud;
    textureCloud.loadFromFile("graphics/cloud.png");
    Sprite spriteCloud1;
    Sprite spriteCloud2;
    Sprite spriteCloud3;
    spriteCloud1.setTexture(textureCloud);
    spriteCloud2.setTexture(textureCloud);
    spriteCloud3.setTexture(textureCloud);

    // position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen// position clouds on the screen
    spriteCloud1.setPosition(0, 0);
    spriteCloud2.setPosition(0, 250);
    spriteCloud3.setPosition(0, 500);

    // are the clouds moving
    bool cloud1Active = false;
    bool cloud2Active = false;
    bool cloud3Active = false;

    // how fast do they move
    float cloud1Speed = 0.0f;
    float cloud2Speed = 0.0f;
    float cloud3Speed = 0.0f;

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
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);

        window.draw(spriteTree);

        window.draw(spriteBee);

        // show everything we just drew
        window.display();

    }

    return 0;
}