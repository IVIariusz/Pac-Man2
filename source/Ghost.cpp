#include "../include/Ghost.h"
#include "../include/Game.h"
#include <algorithm>
#include <random>

Ghost::Ghost() : Entity(), target(0, 0), rng(std::random_device()()), mode(GhostMode::Scatter) {
    setPredefinedAnimation();
    scatterDuration = 7.0f;
    chaseDuration = 20.0f;
    frightenedDuration = 5.0f;
    modeClock.restart();
}

void Ghost::setPredefinedAnimation() {
    animationFrames.clear();
    for (int i = 0; i < 2; ++i) {
        animationFrames.emplace_back(i * 32, 0, 32, 32);
    }
    entitySprite.setTextureRect(animationFrames[0]);
    entitySprite.setOrigin(animationFrames[0].width / 2.0f, animationFrames[0].height / 2.0f);
}

void Ghost::update(float deltaTime) {
    updateMode();
    Game* game = Game::getInstance(); // Access the singleton instance of Game
    sf::Vector2i nextPosition = getPosition() + direction * static_cast<int>(speed * deltaTime);
    if (!game->canMoveTo(nextPosition, direction)) {
        direction = findAlternativeDirection();
    }

    move(deltaTime);

    if (animationClock.getElapsedTime() >= frameDuration) {
        currentFrame = (currentFrame + 1) % animationFrames.size();
        entitySprite.setTextureRect(animationFrames[currentFrame]);
        animationClock.restart();
    }
}

void Ghost::setTarget(const sf::Vector2i& target) {
    this->target = target;
}

void Ghost::setRandomDirection() {
    direction = getRandomDirection();
}

void Ghost::setChasePacman(const sf::Vector2i& pacmanPosition) {
    setMode(GhostMode::Chase);
    target = pacmanPosition;
}

void Ghost::setScatterMode(const sf::Vector2i& scatterTarget) {
    setMode(GhostMode::Scatter);
    target = scatterTarget;
}

void Ghost::setFrightenedMode() {
    setMode(GhostMode::Frightened);
    setRandomDirection();
}

void Ghost::setMode(GhostMode newMode) {
    mode = newMode;
    modeClock.restart();
}

GhostMode Ghost::getMode() const {
    return mode;
}

sf::Vector2i Ghost::getRandomDirection() {
    std::uniform_int_distribution<int> dist(0, 3);
    int dir = dist(rng);
    switch (dir) {
        case 0: return {1, 0};
        case 1: return {-1, 0};
        case 2: return {0, 1};
        case 3: return {0, -1};
        default: return {0, 0};
    }
}

sf::Vector2i Ghost::findAlternativeDirection() {
    std::vector<sf::Vector2i> possibleDirections = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    std::shuffle(possibleDirections.begin(), possibleDirections.end(), rng);
    Game* game = Game::getInstance(); // Access the singleton instance of Game

    for (const auto& dir : possibleDirections) {
        sf::Vector2i nextPosition = getPosition() + dir;
        if (game->canMoveTo(nextPosition, dir)) {
            return dir;
        }
    }

    return {0, 0};
}

void Ghost::updateMode() {
    float elapsed = modeClock.getElapsedTime().asSeconds();

    if (mode == GhostMode::Scatter && elapsed >= scatterDuration) {
        setMode(GhostMode::Chase);
    } else if (mode == GhostMode::Chase && elapsed >= chaseDuration) {
        setMode(GhostMode::Scatter);
    } else if (mode == GhostMode::Frightened && elapsed >= frightenedDuration) {
        setMode(GhostMode::Chase);
    }
}

void Ghost::updateTarget(const sf::Vector2i& pacmanPosition, const sf::Vector2i& blinkyPosition) {
    switch (mode) {
        case GhostMode::Chase:
            target = pacmanPosition;
            break;
        case GhostMode::Scatter:
            break;
        case GhostMode::Frightened:
            setRandomDirection();
            break;
    }
}
