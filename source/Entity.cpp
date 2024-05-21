#include "../include/Entity.h"
#include "../include/Game.h"

Entity::Entity() : speed(0), direction(0, 0), currentFrame(0), frameDuration(sf::seconds(0.5f)) {}

void Entity::move(float deltaTime) {
    sf::Vector2f newPos = entitySprite.getPosition() + sf::Vector2f(direction.x * speed * deltaTime, direction.y * speed * deltaTime);
    entitySprite.setPosition(newPos);
}

void Entity::setSprite(const sf::Sprite& sprite) {
    entitySprite = sprite;
    entitySprite.setOrigin(entitySprite.getTextureRect().width / 2.0f, entitySprite.getTextureRect().height / 2.0f);
}

void Entity::setTexture(const sf::Texture &texture) {
    entitySprite.setTexture(texture);
    if (!animationFrames.empty()) {
        entitySprite.setTextureRect(animationFrames[0]);
        entitySprite.setOrigin(animationFrames[0].width / 2.0f, animationFrames[0].height / 2.0f);
    }
}

sf::Sprite& Entity::getSprite() {
    return entitySprite;
}

sf::Vector2i Entity::getPosition() const {
    sf::Vector2f pos = entitySprite.getPosition();
    return sf::Vector2i(static_cast<int>(pos.x), static_cast<int>(pos.y));
}

void Entity::setDirection(const sf::Vector2i& dir) {
    direction = dir;
    updateDirection();
}

sf::Vector2i Entity::getDirection() const {
    return direction;
}

void Entity::setSpeed(int spd) {
    speed = spd;
}

int Entity::getSpeed() const {
    return speed;
}

void Entity::setSize(float width, float height) {
    sf::Vector2u textureSize = entitySprite.getTexture()->getSize();
    entitySprite.setScale(width / (textureSize.x / (textureSize.x/textureSize.y)), height / textureSize.y);
}

void Entity::update(float deltaTime) {
    move(deltaTime);

    if (animationClock.getElapsedTime() >= frameDuration) {
        currentFrame = (currentFrame + 1) % animationFrames.size();
        entitySprite.setTextureRect(animationFrames[currentFrame]);
        animationClock.restart();
    }
}

void Entity::render(sf::RenderWindow& window) const {
    window.draw(entitySprite);
}

void Entity::setPosition(const sf::Vector2u& pos) {
    entitySprite.setPosition(static_cast<float>(pos.x), static_cast<float>(pos.y));
}

void Entity::updateDirection() {
    if (direction.x > 0) {
        entitySprite.setRotation(0);
    } else if (direction.x < 0) {
        entitySprite.setRotation(180);
    } else if (direction.y > 0) {
        entitySprite.setRotation(90);
    } else if (direction.y < 0) {
        entitySprite.setRotation(270);
    }
}
