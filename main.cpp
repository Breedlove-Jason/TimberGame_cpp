#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Time.hpp>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <cmath>
#include <sstream>
#include <string>
#include <random>
#include <vector>

#include "LoadResources.h"
#include "MoveableObject.h"

using namespace sf;
namespace fs = std::filesystem;
using namespace std;

// function header
void updateBranches(int seed);

const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

// where is the player/branch?
enum class side {
    LEFT, RIGHT, NONE
};

side branchPositions[NUM_BRANCHES];

// Create a random number generator
std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());

// Function to generate random numbers within a range
int generateRandom(int min, int max) {
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

int globalRand = generateRandom(1, 100) % 100;
sf::Time dt;

int main() {
    int score = 0;

    Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");
    Text messageText;
    Text scoreText;

    //What is the value of pi?
    const float valuePi = M_PI;

    bool isAlive = true;


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
    // fs::path pathToImage = fs::current_path() / "graphics/background.png";
    // cout << "Full path to image: " << pathToImage << std::endl;
    //
    // ifstream file(pathToImage);
    // if (file.good()) {
    //     cout << "File exists" << std::endl;
    // } else {
    //     cout << "File does not exist" << std::endl;
    // }
    // create a video mode object
    VideoMode vm(1920, 1080);

    // create and open a window for the game
    RenderWindow window(vm, "Timber!!!"); // set style to fullscreen when ready Style::Fullscreen

    LoadResources background(window, "background", "spriteBackground", "graphics/background.png", 0, 0, Vector2f(0, 0),
                             0.0f);

    LoadResources tree(window, "tree", "spriteTree", "graphics/tree.png", 810, 0, Vector2f(0, 0), 0.0f);

    MovableObject bee(window, "bee", "spriteBee", "graphics/bee.png", 0, 800, Vector2f(-1.0f, 0.0f), 200.0f);
    MovableObject cloud1(window, "cloud1", "spriteCloud1", "graphics/cloud.png", 0, 0, Vector2f(-1.0f, 0.0f), .5f);
    MovableObject cloud2(window, "cloud2", "spriteCloud2", "graphics/cloud.png", 0, 250, Vector2f(-1.0f, 0.0f), .5f);
    MovableObject cloud3(window, "cloud3", "spriteCloud3", "graphics/cloud.png", 0, 500, Vector2f(-1.0f, 0.0f), .5f);

    // In your game loop
    // bee.moveObject(dt.asSeconds(), 200, 500, 10);
    // cloud1.moveObject(dt.asSeconds(), 200, 150, 10);
    // cloud2.moveObject(dt.asSeconds(), 200, 300, 20);
    // cloud3.moveObject(dt.asSeconds(), 200, 450, 30);

    // prepare the clouds
    // Texture textureCloud;
    // textureCloud.loadFromFile("graphics/cloud.png");
    // Sprite spriteCloud1;
    // Sprite spriteCloud2;
    // Sprite spriteCloud3;
    // spriteCloud1.setTexture(textureCloud);
    // spriteCloud2.setTexture(textureCloud);
    // spriteCloud3.setTexture(textureCloud);
    //
    // // position clouds on the screen
    // spriteCloud1.setPosition(0, 0);
    // spriteCloud2.setPosition(0, 250);
    // spriteCloud3.setPosition(0, 500);
    //
    // // are the clouds moving
    // bool cloud1Active = false;
    // bool cloud2Active = false;
    // bool cloud3Active = false;
    //
    // // how fast do they move
    // float cloud1Speed = 0.0f;
    // float cloud2Speed = 0.0f;
    // float cloud3Speed = 0.0f;

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

    // control player input
    bool acceptInput = false;

    // After loading textures and setting up sprites
    Texture textureExtraTree;
    textureExtraTree.loadFromFile("graphics/tree2.png");
    Sprite extraTree1(textureExtraTree), extraTree2(textureExtraTree);
    extraTree1.setPosition(300, -125);
    extraTree2.setPosition(1400, -200);

    // Initialize FPS variables and text
    Clock fpsClock;
    Text fpsText;
    fpsText.setFont(font);
    fpsText.setCharacterSize(24);
    fpsText.setFillColor(Color::White);
    fpsText.setPosition(1500, 50); // Position the FPS counter on the screen

    // chopping sound
    SoundBuffer chopBuffer;
    chopBuffer.loadFromFile("sound/chop.wav");
    Sound chop;
    chop.setBuffer(chopBuffer);

    // death sound
    SoundBuffer deathBuffer;
    deathBuffer.loadFromFile("sound/death.wav");
    Sound death;
    death.setBuffer(deathBuffer);

    // out of time sound
    SoundBuffer ootBuffer;
    ootBuffer.loadFromFile("sound/out_of_time.wav");
    Sound outOfTime;
    outOfTime.setBuffer(ootBuffer);

    // game loop
    while (window.isOpen()) {
        /*
         * ****************************************************
         * Handle the player input
         * ****************************************************
         */

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyReleased && !paused) {
                // listen for key presses again
                acceptInput = true;

                // hide the axe
                spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
            }
        }


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
        for (auto&branch: branches) {
            branch.setTexture(textureBranch);
            branch.setPosition(-2000, -2000);
            branch.setOrigin(220, 20);
        }

        if (Keyboard::isKeyPressed((Keyboard::Escape))) {
            window.close();
        }
        // start the game
        if (Keyboard::isKeyPressed(Keyboard::Return)) {
            paused = false;
            score = 0;
            timeRemaining = 6;

            // make branches disappear
            for (int i = 1; i < NUM_BRANCHES; i++) {
                branchPositions[i] = side::NONE;
            }
            // make sure gravestone is hidden
            spriteRIP.setPosition(675, 2000);

            // move player into position
            spritePlayer.setPosition(675, 660);

            acceptInput = true;
        }
        // wrap player controls to accept input
        if (acceptInput) {
            // handle right key press
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                playerSide = side::RIGHT;
                score++;
                timeRemaining += (2 / score) + .15;
                spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);
                spritePlayer.setPosition(1200, 720);
                updateBranches(score);
                spriteLog.setPosition(810, 720);
                logSpeedX = -5000; // Moves left
                logActive = true;
                acceptInput = false;
                chop.play();
            }

            // handle left key press
            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                playerSide = side::LEFT;
                score++;
                timeRemaining += (2 / score) + .15;
                spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);
                spritePlayer.setPosition(580, 720);
                updateBranches(score);
                spriteLog.setPosition(810, 720);
                logSpeedX = 5000; // Moves right
                logActive = true;
                acceptInput = false;
                chop.play();
            }
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

            if (timeRemaining <= 0.0f) {
                // pause the game
                paused = true;

                // change message shown to player
                messageText.setString("Out of time!!");

                // reposition text based off new size
                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.left + textRect.width / 2.0f,
                                      textRect.top + textRect.height / 2.0f);

                messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

                // play out of time sound
                outOfTime.play();
            }

            // move the lcouds and the bee
            // In your game loop
            bee.moveObject(dt.asSeconds(), 200, 500, 10);
            cloud1.moveObject(dt.asSeconds(), 200, 150, 10);
            cloud2.moveObject(dt.asSeconds(), 200, 300, 20);
            cloud3.moveObject(dt.asSeconds(), 200, 450, 30);            // setup the bee
            // if (!bee.isActive()) {
            //     // how fast is the bee
            //     bee.setSpeed((rand() % 200) + 200);
            //
            //     // how high is the bee
            //     float height = (rand() % 500) + 500;
            //     bee.setDirection(-1.0f, 0.0f); // Make the bee move to the left
            //     bee.setActive(true);
            // }
            // else {
            //     // move the bee
            //     bee.move(dt.asSeconds());
            //     if (bee.getSprite().getPosition().x < -100) {
            //         bee.setActive(false);
            //     }
            // }
            // // manage the clouds
            // // cloud 1
            // if (!cloud1Active) {
            //     // how fast is the cloud
            //     srand((int)time(0) * 10);
            //     cloud1Speed = (rand() % 200);
            //
            //     // how high is the cloud
            //     srand((int)time(0) * 10);
            //     float height = (rand() % 150);
            //     spriteCloud1.setPosition(-200, height);
            //
            //     cloud1Active = true;
            // }
            // else {
            //     spriteCloud1.setPosition(spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()),
            //                              spriteCloud1.getPosition().y);
            //
            //     // has the cloud reached the right hand edge of the screen?
            //     if (spriteCloud1.getPosition().x > 1920) {
            //         cloud1Active = false;
            //     }
            // }
            // // cloud 2
            // if (!cloud2Active) {
            //     // how fast is the cloud
            //     srand((int)time(0) * 20);
            //     cloud2Speed = (rand() % 200);
            //
            //     // how high is the cloud
            //     srand((int)time(0) * 20);
            //     float height = (rand() % 300) - 150;
            //     spriteCloud2.setPosition(-200, height);
            //
            //     cloud2Active = true;
            // }
            // else {
            //     spriteCloud2.setPosition(spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()),
            //                              spriteCloud2.getPosition().y);
            //
            //     // has the cloud reached the right hand edge of the screen?
            //     if (spriteCloud2.getPosition().x > 1920) {
            //         cloud2Active = false;
            //     }
            // }
            // if (!cloud3Active) {
            //     // how fast is the cloud
            //     srand((int)time(0) * 30);
            //     cloud3Speed = (rand() % 200);
            //
            //     // how high is the cloud
            //     srand((int)time(0) * 30);
            //     float height = (rand() % 450) - 150;
            //     spriteCloud3.setPosition(-200, height);
            //
            //     cloud3Active = true;
            // }
            // else {
            //     spriteCloud3.setPosition(spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()),
            //                              spriteCloud3.getPosition().y);
            //
            //     // has the cloud reached the right hand edge of the screen?
            //     if (spriteCloud3.getPosition().x > 1920) {
            //         cloud3Active = false;
            //     }
            // }
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
                }
                else if (branchPositions[i] == side::RIGHT) {
                    // move the sprite to the right side
                    branches[i].setPosition(1330, height);
                    // set the sprite rotation to normal
                    branches[i].setRotation(0);
                }
                else {
                    // hide the branch
                    branches[i].setPosition(3000, height);
                }
            }
            if (logActive) {
                spriteLog.setPosition(spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()),
                                      spriteLog.getPosition().y + (logSpeedY * dt.asSeconds()));
                // has the log reached the right hand edge?
                if (spriteLog.getPosition().x < -100 || spriteLog.getPosition().x > 2000) {
                    logActive = false;
                    spriteLog.setPosition(810, 720);
                }
            }
            // has the player been squished by a branch?
            if (branchPositions[5] == playerSide) {
                paused = true;
                acceptInput = false;

                // Display gravestone and update the message
                spriteRIP.setPosition(525, 760);
                spritePlayer.setPosition(2000, 660); // Hide player
                messageText.setString("SQUISHED!!");
                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.width / 2, textRect.height / 2);
                messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
                death.play();
            }
        } // end of if(!paused)

        /*
         * ****************************************************
         * Draw the scene
         * ****************************************************
         */

        // clear screen
        window.clear();

        background.draw();
        tree.draw();
        bee.draw();

        cloud1.draw();
        cloud2.draw();
        cloud3.draw();
        //
        // window.draw(spriteCloud1);
        // window.draw(spriteCloud2);
        // window.draw(spriteCloud3);
        for (auto&branch: branches) {
            window.draw(branch);
        }
        window.draw(extraTree1);
        window.draw(extraTree2);
        window.draw(spritePlayer);
        window.draw(spriteAxe);
        window.draw(spriteLog);
        window.draw(spriteRIP);
        window.draw(timeBar);
        window.draw(scoreText);
        if (paused) {
            window.draw(messageText);
        }

        float currentTime = fpsClock.restart().asSeconds();
        float fps = 1.f / currentTime;
        fpsText.setString("FPS: " + to_string(static_cast<int>(fps)));
        window.draw(fpsText); // Draw FPS text

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
    srand((int)time(0) + seed);
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

// Sprite setupSprite(const string &filename, float posX, float posY) {
//     Texture texture;
//     if (!texture.loadFromFile(filename)) {
//         cout << "Can't load " << filename << endl;
//     } else {
//         cout << filename << " loaded" << endl;
//     }
//     Sprite sprite;
//     sprite.setTexture(texture);
//     sprite.setPosition(posX, posY);
//     return sprite;
// }
