#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <vector>

class Entity {
protected:
    sf::Sprite entitySprite;
    sf::Vector2i direction;
    int speed;

    // Animacja
    std::vector<sf::IntRect> animationFrames;
    size_t currentFrame;
    sf::Clock animationClock;
    sf::Time frameDuration;

    virtual void updateDirection();

public:
    Entity();
    virtual ~Entity() = default;

    void move(float deltaTime);
    void setSprite(const sf::Sprite& sprite);
    void setTexture(const sf::Texture &texture);
    sf::Sprite& getSprite();
    sf::Vector2i getDirection() const;
    sf::Vector2i getPosition() const;
    void setDirection(const sf::Vector2i& dir);
    void setPosition(const sf::Vector2u& pos);
    void setSpeed(int spd);
    int getSpeed() const;

    void setSize(float width, float height);
    virtual void update(float deltaTime);
    void render(sf::RenderWindow& window) const;

    virtual void setPredefinedAnimation() = 0; // Pure virtual function
    bool canMoveTo(const sf::Vector2i& position, const sf::Vector2i& direction); // Deklaracja metody
};

#endif // ENTITY_H
