#include "../include/Score.h"

Score::Score() : currentScore(0) {
    if (!font.loadFromFile("../assets/fonts/arial.ttf")) {
        throw std::runtime_error("Nie można załadować czcionki");
    }

    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);
    scoreText.setString("Score: 0");
}

void Score::addPoints(int points) {
    currentScore += points;
    scoreText.setString("Score: " + std::to_string(currentScore));
}

void Score::reset() {
    currentScore = 0;
    scoreText.setString("Score: 0");
}

void Score::draw(sf::RenderWindow& window) {
    window.draw(scoreText);
}

void Score::setPosition(sf::Vector2u pos) {
    scoreText.setPosition(pos.x, pos.y);
}