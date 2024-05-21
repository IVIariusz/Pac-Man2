#include "../include/point.h"

void point::setPoint(sf::Texture &pointTexture, sf::Vector2u pos, int _type) {
    pointSprite.setTexture(pointTexture);
    pointSprite.setPosition(static_cast<float>(pos.x), static_cast<float>(pos.y));
    type = _type;

    if(type == 2) pointSprite.setScale(sf::Vector2f(1.5f, 1.5f));

    pointSprite.setOrigin(pointSprite.getLocalBounds().width / 2.0f, pointSprite.getLocalBounds().height / 2.0f);
}

int point::EatPoint() {
    Eaten = true;
    return (type == 1) ? 10 : 50;
}

bool point::isEaten() const {
    return Eaten;
}
