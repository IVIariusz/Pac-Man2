#ifndef POINT_H
#define POINT_H

#include <SFML/Graphics.hpp>

class point {
public:
    void setPoint(sf::Texture &pointTexture, sf::Vector2u pos, int _type);
    int EatPoint();
    bool isEaten() const;
    const sf::Sprite& getSprite() const { return pointSprite; }

private:
    sf::Sprite pointSprite;
    int type;
    bool Eaten = false;
};

#endif // POINT_H
