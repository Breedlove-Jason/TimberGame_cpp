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

    // create a clock object
    Clock clock;




    // check graphics module is working
    fs::path pathToImage = fs::current_path() / "graphics/background.png";
    std::cout << "Full path to image: " << pathToImage << std::endl;

    std::ifstream file(pathToImage);
    if (file.good()) {
        std::cout << "File exists" << std::endl;
    } else {
        std::cout << "File does not exist" << std::endl;
    }
    // create a video mode object
    VideoMode vm(1920, 1080);

    // create and open a window for the game
    RenderWindow window(vm, "Timber!!!"); // set style to fullscreen when ready Style::Fullscreen

    // create a texture to hold a graphic on the GPU
    Texture textureBackground;

    // load a graphic into the texture
    textureBackground.loadFromFile("graphics/background.png");


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
    } else {
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
        if (Keyboard::isKeyPressed((Keyboard::Escape))) {
            window.close();
        }

        /*
         * ****************************************************
         * Update the scene
         * ****************************************************
         */
        Time dt = clock.restart();

        // setup the bee
        if(!beeActive){
            // how fast is the bee
            srand((int)time(0));
            beeSpeed = (rand() % 200) + 200;

            // how high is the bee
            srand((int)time(0) * 10);
            float height = (rand() % 500) + 500;
            spriteBee.setPosition(2000, height);
            beeActive =true;
        }else{
            // move the bee
            spriteBee.setPosition(spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()), spriteBee.getPosition().y);
            if (spriteBee.getPosition().x < -100) {
                beeActive = false;
            }
        }

        // manage the clouds
        // cloud 1
        if (!cloud1Active){

            // how fast is the cloud
            srand((int) time (0) * 10);
            cloud1Speed = (rand() % 200);

            // how high is the cloud
            srand((int) time (0) * 10);
            float height = (rand() % 150);
            spriteCloud1.setPosition(-200, height);

            cloud1Active = true;
        }else{
            spriteCloud1.setPosition(spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()), spriteCloud1.getPosition().y);

            // has the cloud reached the right hand edge of the screen?
            if (spriteCloud1.getPosition().x > 1920){
                cloud1Active = false;
            }
        }
        // cloud 2
        if (!cloud2Active){

            // how fast is the cloud
            srand((int) time (0) * 20);
            cloud2Speed = (rand() % 200);

            // how high is the cloud
            srand((int) time (0) * 20);
            float height = (rand() % 300) - 150;
            spriteCloud2.setPosition(-200, height);

            cloud2Active = true;
        }else{
            spriteCloud2.setPosition(spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()), spriteCloud2.getPosition().y);

            // has the cloud reached the right hand edge of the screen?
            if (spriteCloud2.getPosition().x > 1920){
                cloud2Active = false;
            }
        }
        if (!cloud3Active){

            // how fast is the cloud
            srand((int) time (0) * 30);
            cloud3Speed = (rand() % 200);

            // how high is the cloud
            srand((int) time (0) * 30);
            float height = (rand() % 450) - 150;
            spriteCloud3.setPosition(-200, height);

            cloud3Active = true;
        }else{
            spriteCloud3.setPosition(spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()), spriteCloud3.getPosition().y);

            // has the cloud reached the right hand edge of the screen?
            if (spriteCloud3.getPosition().x > 1920){
                cloud3Active = false;
            }
        }



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