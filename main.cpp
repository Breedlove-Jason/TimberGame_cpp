#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <cmath>
#include <sstream>
#include <cstdio>

#include "Timber.h"

using namespace sf;
namespace fs = std::filesystem;
using namespace std;

// function declaration
void updateBranches(int seed);

const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

// where is the player/branch?
// left or right
enum class side{ LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];

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

    // time bar
    RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

    Time gameTimeTotal;
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

    // track if game is running
    bool paused = true;



    // check graphics module is working
    fs::path pathToImage = fs::current_path() / "graphics/background.png";
    cout << "Full path to image: " << pathToImage << std::endl;

    ifstream file(pathToImage);
    if (file.good()) {
        cout << "File exists" << std::endl;
    } else {
        cout << "File does not exist" << std::endl;
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

    // position clouds on the screen
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

    // prepare the player
    Texture texturePlayer;
    texturePlayer.loadFromFile("graphics/player.png");
    Sprite spritePlayer;
    spritePlayer.setTexture(texturePlayer);
    spritePlayer.setPosition(580, 720);

    // player starts on left
    side playerSide = side::LEFT;

    // prepare the gravestone
    Texture textureRIP;
    textureRIP.loadFromFile("graphics/rip.png");
    Sprite spriteRIP;
    spriteRIP.setTexture(textureRIP);
    spriteRIP.setPosition(600, 860);

    // prepare the axe
    Texture textureAxe;
    textureAxe.loadFromFile("graphics/axe.png");
    Sprite spriteAxe;
    spriteAxe.setTexture(textureAxe);
    spriteAxe.setPosition(700, 830);

    // align axe with tree
    const float AXE_POSITION_LEFT = 700;
    const float AXE_POSITION_RIGHT = 1075;

    // prepare the flying log
    Texture textureLog;
    textureLog.loadFromFile("graphics/log.png");
    Sprite spriteLog;
    spriteLog.setTexture(textureLog);
    spriteLog.setPosition(810, 720);

    // log related variables
    bool logActive = false;
    float logSpeedX = 1000;
    float logSpeedY = -1500;

    // game loop
    while (window.isOpen()) {
        /*
         * ****************************************************
         * Handle the player input
         * ****************************************************
         */
        // draw some text
        int score = 0;
        Text messageText;
        Text scoreText;

        // choose a font
        Font font;
        font.loadFromFile("fonts/KOMIKAP_.ttf");

        // set the font to message
        messageText.setFont(font);
        scoreText.setFont(font);

        // assign the message
        messageText.setString("Press Enter to start!");
        scoreText.setString("Score = 0");

        // enlarge font text
        messageText.setCharacterSize(75);
        scoreText.setCharacterSize(100);

        // font color
        messageText.setFillColor(Color::White);
        scoreText.setFillColor(Color::White);

        // position the text
        FloatRect textRect = messageText.getLocalBounds();
        messageText.setOrigin(textRect.left + textRect.width / 2.0f,
                              textRect.top + textRect.height / 2.0f);

        messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
        scoreText.setPosition(20, 20);

        // prepare the 6 branches
        Texture textureBranch;
        textureBranch.loadFromFile("graphics/branch.png");

        // set the texture for each branch sprite
        for(int i = 0; i < NUM_BRANCHES; i++) {
            branches[i].setTexture(textureBranch);
            branches[i].setPosition(-2000, -2000);
            branches[i].setOrigin(220, 20);
        }

        if (Keyboard::isKeyPressed((Keyboard::Escape))) {
            window.close();
        }
        // start the game
        if (Keyboard::isKeyPressed(Keyboard::Return)) {
            paused = false;
            score = 0;
            timeRemaining = 6;
        }
        /*
         * ****************************************************
         * Update the scene
         * ****************************************************
         */
        if (!paused) {
            // measure time

            Time dt = clock.restart();

            // subtract from time remaining
            timeRemaining -= dt.asSeconds();

            // size up time bar
            timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

            if (timeRemaining <= 0.0f){
                // pause the game
                paused = true;

                // change message shown to player
                messageText.setString("Out of time!!");

                // reposition text based off new size
                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.left + textRect.width / 2.0f,
                                      textRect.top + textRect.height / 2.0f);

                messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
            }

            // setup the bee
            if (!beeActive) {
                // how fast is the bee
                srand((int) time(0));
                beeSpeed = (rand() % 200) + 200;

                // how high is the bee
                srand((int) time(0) * 10);
                float height = (rand() % 500) + 500;
                spriteBee.setPosition(2000, height);
                beeActive = true;
            } else {
                // move the bee
                spriteBee.setPosition(spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()),
                                      spriteBee.getPosition().y);
                if (spriteBee.getPosition().x < -100) {
                    beeActive = false;
                }
            }

            // manage the clouds
            // cloud 1
            if (!cloud1Active) {

                // how fast is the cloud
                srand((int) time(0) * 10);
                cloud1Speed = (rand() % 200);

                // how high is the cloud
                srand((int) time(0) * 10);
                float height = (rand() % 150);
                spriteCloud1.setPosition(-200, height);

                cloud1Active = true;
            } else {
                spriteCloud1.setPosition(spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()),
                                         spriteCloud1.getPosition().y);

                // has the cloud reached the right hand edge of the screen?
                if (spriteCloud1.getPosition().x > 1920) {
                    cloud1Active = false;
                }
            }
            // cloud 2
            if (!cloud2Active) {

                // how fast is the cloud
                srand((int) time(0) * 20);
                cloud2Speed = (rand() % 200);

                // how high is the cloud
                srand((int) time(0) * 20);
                float height = (rand() % 300) - 150;
                spriteCloud2.setPosition(-200, height);

                cloud2Active = true;
            } else {
                spriteCloud2.setPosition(spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()),
                                         spriteCloud2.getPosition().y);

                // has the cloud reached the right hand edge of the screen?
                if (spriteCloud2.getPosition().x > 1920) {
                    cloud2Active = false;
                }
            }
            if (!cloud3Active) {

                // how fast is the cloud
                srand((int) time(0) * 30);
                cloud3Speed = (rand() % 200);

                // how high is the cloud
                srand((int) time(0) * 30);
                float height = (rand() % 450) - 150;
                spriteCloud3.setPosition(-200, height);

                cloud3Active = true;
            } else {
                spriteCloud3.setPosition(spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()),
                                         spriteCloud3.getPosition().y);

                // has the cloud reached the right hand edge of the screen?
                if (spriteCloud3.getPosition().x > 1920) {
                    cloud3Active = false;
                }
            }
            // update score text
            stringstream ss;
            ss << "Score = " << score;
            scoreText.setString(ss.str());

            // update the branch sprites
            for (int i = 0; i < NUM_BRANCHES; i++) {
                float height = i * 150;
                if (branchPositions[i] == side::LEFT) {
                    // move the sprite to the left side
                    branches[i].setPosition(610, height);
                    // flip the sprite round the other way
                    branches[i].setRotation(180);
                } else if (branchPositions[i] == side::RIGHT) {
                    // move the sprite to the right side
                    branches[i].setPosition(1330, height);
                    // set the sprite rotation to normal
                    branches[i].setRotation(0);
                } else {
                    // hide the branch
                    branches[i].setPosition(3000, height);
                }
            }
        } // end of if(!paused)


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

        // draw branches
        for (int i = 0; i < NUM_BRANCHES; i++) {
            window.draw(branches[i]);
        }
        updateBranches(1);
        updateBranches(2);
        updateBranches(3);
        updateBranches(4);
        updateBranches(5);

        // draw tree
        window.draw(spriteTree);

        // draw player
        window.draw(spritePlayer);

        // draw axe
        window.draw(spriteAxe);

        // draw log
        window.draw(spriteLog);

        // draw gravestone
        window.draw(spriteRIP);


        window.draw(timeBar);

        window.draw(spriteBee);

        // draw the score
        window.draw(scoreText);
        if (paused) {
            window.draw(messageText);
        }

        // show everything we just drew
        window.display();

    }

    return 0;
}

void updateBranches(int seed) {
    // move all the branches down one place
    for (int j = NUM_BRANCHES - 1; j > 0; j--) {
        branchPositions[j] = branchPositions[j - 1];
    }

    // spawn a new branch at position 0
    srand((int) time(0) + seed);
    int r = (rand() % 5);
    switch (r) {
        case 0:
            branchPositions[0] = side::LEFT;
            break;
        case 1:
            branchPositions[0] = side::RIGHT;
            break;
        default:
            branchPositions[0] = side::NONE;
            break;
    }
}
