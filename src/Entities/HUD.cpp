#include "HUD.h"
#include "../Managers/ResourceManager.h"

using namespace std;
using namespace sf;

HUD::HUD() {
    // Load the font from the resource manager or directly if not managed
    if (!font.loadFromFile("fonts/KOMIKAP_.ttf")) {
        throw runtime_error("Failed to load font: fonts/KOMIKAP_.ttf");
    }

    // Initialize scoreText
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(50, 20);  // Example position, adjust based on layout

    // Initialize timeText
    timeText.setFont(font);
    timeText.setCharacterSize(24);
    timeText.setFillColor(Color::White);
    timeText.setPosition(50, 50);  // Example position, adjust based on layout
}

void HUD::updateScore(int score) {
    scoreText.setString("Score: " + to_string(score));
}

void HUD::updateTime(float time) {
    timeText.setString("Time Remaining: " + to_string(static_cast<int>(time)) + "s");
}

void HUD::draw(RenderWindow &window) {
    window.draw(scoreText);
    window.draw(timeText);
}

