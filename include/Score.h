#ifndef SCORE_H
#define SCORE_H

#include <SFML/Graphics.hpp>

class Score {
public:
    Score();
    void addPoints(int points);
    void reset();
    void draw(sf::RenderWindow& window);
    void setPosition(sf::Vector2u pos);

private:
    int currentScore;
    sf::Font font;
    sf::Text scoreText;
};

#endif // SCORE_H
