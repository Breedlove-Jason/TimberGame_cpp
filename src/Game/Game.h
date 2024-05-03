# ifndef  GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "../Entities/Player.h"
#include "../Entities/Branch.h"
#include "../Entities/Background.h"
#include "../Entities/Cloud.h"
#include "../Managers/ResourceManager.h"
#include "../Entities/Tree.h"
#include "../Entities/HUD.h"

using namespace std;
using namespace sf;

class Game {
public:
    Game();
    void run();
private:
    RenderWindow window;
    bool isPaused;

    Background background;
    Player player;
    vector<Tree> trees;
    vector<Branch> branches;
    vector<Cloud> clouds;
    Tree tree;
    HUD hud;

    void processEvents();

    void update(Time deltaTime);

    void render();

    void checkCollisions();

    void handleGameLogic();
};
#endif
