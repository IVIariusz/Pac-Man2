#ifndef GHOST_H
#define GHOST_H

#include "Entity.h"
#include <random>
#include <vector>
#include <SFML/System/Vector2.hpp>

enum class GhostMode { Chase, Scatter, Frightened };

class Ghost : public Entity {
public:
    Ghost();
    virtual ~Ghost() = default;

    void setPredefinedAnimation() override;
    void update(float deltaTime) override;

    void setTarget(const sf::Vector2i& target);
    void setRandomDirection();
    void setChasePacman(const sf::Vector2i& pacmanPosition);
    void setScatterMode(const sf::Vector2i& scatterTarget);
    void setFrightenedMode();

    void setMode(GhostMode mode);
    GhostMode getMode() const;

    void updateTarget(const sf::Vector2i& pacmanPosition, const sf::Vector2i& blinkyPosition);

private:
    std::vector<sf::IntRect> animationFrames;
    sf::Vector2i target;
    std::mt19937 rng;
    GhostMode mode;

    sf::Clock modeClock;
    float scatterDuration;
    float chaseDuration;
    float frightenedDuration;

    sf::Vector2i getRandomDirection();
    sf::Vector2i findAlternativeDirection();
    void updateMode();
};

#endif // GHOST_H
