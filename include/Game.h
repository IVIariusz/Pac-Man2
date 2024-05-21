#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "../include/Board.h"
#include "../include/Pacman.h"
#include "../include/Ghost.h"
#include "../include/Score.h"

class Game {
public:
    Game();
    ~Game();
    void run();
    static Game* getInstance();

    bool canMoveTo(const sf::Vector2i& position, const sf::Vector2i& direction);

private:
    void render();
    void shutdown();
    void takeInput();
    void initialize();
    void initializeGhosts();
    void update(float deltaTime);
    void checkCollisions();

    static Game* instance;

    sf::RenderWindow window;
    Board board;
    Pacman pacman;
    std::vector<Ghost> ghosts;
    std::vector<sf::Sprite> staticSprites;
    std::vector<point> GamePoints;
    sf::Texture pacmanTexture;
    sf::Texture ghostTexture;
    sf::Vector2i direction;
    float deltaTime;
    bool isRunning;
    Score score;
};

#endif // GAME_H
