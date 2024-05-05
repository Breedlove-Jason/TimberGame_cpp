#ifndef PLAYER_H  // Include guard to prevent multiple includes
#define PLAYER_H

#include <SFML/Graphics.hpp> // You might need this for Sprite

enum class Side { LEFT, RIGHT }; // Assuming your Side enum is not defined elsewhere

class Player {
public:
    // Constructor
    Player(int initialX, int initialY);

    // Member Functions (Behaviors)
    void moveLeft();
    void moveRight();
    void chop();
    void updateIdleTime(float deltaTime);
    bool takeDamage();
    int getScore() const;

private:
    // Member Variables (Properties)
    int m_positionX;
    int m_positionY;
    int m_score;
    float m_idleTime;
    float m_maxIdleTime;
    Side m_playerSide;

    // You MAY include these if tightly coupled with Player logic:
    sf::Sprite m_spritePlayer;
    sf::Sprite m_spriteAxe;
};

#endif // PLAYER_H
