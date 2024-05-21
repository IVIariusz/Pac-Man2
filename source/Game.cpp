#include "../include/Game.h"
#include "../include/setting.h"
#include <iostream>

Game* Game::instance = nullptr;

Game::Game() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT + 100), "Pacman"), board(ASSET_MAP_PATH), pacman() {
    instance = this;
    initialize();
    run();
}

Game::~Game() {
    shutdown();
    instance = nullptr;
}

Game* Game::getInstance() {
    return instance;
}

void Game::run() {
    isRunning = true;
    sf::Clock clock;
    while (window.isOpen() && isRunning) {
        deltaTime = clock.restart().asSeconds();
        takeInput();
        update(deltaTime);
        render();
    }
}

void Game::render() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::Resized) {
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            window.setView(sf::View(visibleArea));
        }
    }
    window.clear();

    for (const auto& sprite : staticSprites) {
        window.draw(sprite);
    }

    for (const auto& point : GamePoints) {
        if (!point.isEaten()) window.draw(point.getSprite());
    }

    pacman.render(window);

    for (auto& ghost : ghosts) {
        ghost.render(window);
    }

    score.draw(window);

    window.display();
}

void Game::shutdown() {

}

void Game::takeInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        direction = {0, -1};
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        direction = {0, 1};
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        direction = {-1, 0};
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        direction = {1, 0};
    }
    pacman.setDirection(direction);
}

void Game::initialize() {
    if (!pacmanTexture.loadFromFile(ASSET_PACMAN_MOVEMENT)) {
        throw std::runtime_error("Nie można załadować tekstury z pliku: " + std::string(ASSET_PACMAN_MOVEMENT));
    }
    if (!ghostTexture.loadFromFile(ASSET_GHOST_MOVEMENT)) {
        throw std::runtime_error("Nie można załadować tekstury z pliku: " + std::string(ASSET_GHOST_MOVEMENT));
    }

    const auto& sprites = board.getSprites();
    staticSprites.insert(staticSprites.end(), sprites.begin(), sprites.end());

    const auto& points = board.getPoints();
    GamePoints.insert(GamePoints.end(), points.begin(), points.end());

    window.setSize(sf::Vector2u(board.getSize().x, board.getSize().y + 80));

    pacman.setSpeed(PACMAN_SPEED);
    pacman.setPosition({board.getEntityPos()[4].x + 8, board.getEntityPos()[4].y + 8});
    pacman.setTexture(pacmanTexture);
    pacman.setPredefinedAnimation();
    pacman.setSize(16.0f, 16.0f);

    initializeGhosts();

    score.setPosition(sf::Vector2u((window.getSize().x / 3), (window.getSize().y - 100)));
}

void Game::initializeGhosts() {
    ghosts.resize(4);

    ghosts[0].setSpeed(GHOST_SPEED);
    ghosts[0].setPosition({board.getEntityPos()[0].x + 8, board.getEntityPos()[0].y + 8});
    ghosts[0].setTexture(ghostTexture);
    ghosts[0].setPredefinedAnimation();
    ghosts[0].setSize(16.0f, 16.0f);
    ghosts[0].setChasePacman(pacman.getPosition());
    ghosts[0].setDirection({1, 0});

    ghosts[1].setSpeed(GHOST_SPEED);
    ghosts[1].setPosition({board.getEntityPos()[1].x + 8, board.getEntityPos()[1].y + 8});
    ghosts[1].setTexture(ghostTexture);
    ghosts[1].setPredefinedAnimation();
    ghosts[1].setSize(16.0f, 16.0f);
    ghosts[1].setChasePacman({1, 1});
    ghosts[1].setDirection({0, -1});

    ghosts[2].setSpeed(GHOST_SPEED);
    ghosts[2].setPosition({board.getEntityPos()[2].x + 8, board.getEntityPos()[2].y + 8});
    ghosts[2].setTexture(ghostTexture);
    ghosts[2].setPredefinedAnimation();
    ghosts[2].setSize(16.0f, 16.0f);
    ghosts[2].setChasePacman({static_cast<int>(board.getSize().x) - 1, 0}); // Inky
    ghosts[2].setDirection({1, 0});

    ghosts[3].setSpeed(GHOST_SPEED);
    ghosts[3].setPosition({board.getEntityPos()[3].x + 8, board.getEntityPos()[3].y + 8});
    ghosts[3].setTexture(ghostTexture);
    ghosts[3].setPredefinedAnimation();
    ghosts[3].setSize(16.0f, 16.0f);
    ghosts[3].setChasePacman({0, static_cast<int>(board.getSize().y) - 1});
    ghosts[3].setDirection({0, 1});
}

void Game::update(float deltaTime) {
    sf::Vector2i nextPacmanPosition = pacman.getPosition() + pacman.getDirection() * static_cast<int>(pacman.getSpeed() * deltaTime);

    if (canMoveTo(nextPacmanPosition, pacman.getDirection())) {
        pacman.update(deltaTime);
    }

    for (auto& ghost : ghosts) {
        ghost.updateTarget(pacman.getPosition(), ghosts[0].getPosition());
        ghost.update(deltaTime);
    }

    checkCollisions();
}

bool Game::canMoveTo(const sf::Vector2i& position, const sf::Vector2i& direction) {
    const auto& mapData = board.getMapData();
    int entitySize = ASSETS_SIZE / 2;
    int margin = 3;

    int x = position.x / ASSETS_SIZE;
    int y = position.y / ASSETS_SIZE;

    if (direction.x > 0) {
        x = (position.x + entitySize + margin) / ASSETS_SIZE;
    } else if (direction.x < 0) {
        x = (position.x - entitySize - margin) / ASSETS_SIZE;
    } else if (direction.y > 0) {
        y = (position.y + entitySize + margin) / ASSETS_SIZE;
    } else if (direction.y < 0) {
        y = (position.y - entitySize - margin) / ASSETS_SIZE;
    }

    if (x < 0 || x >= mapData[0].size() || y < 0 || y >= mapData.size()) {
        return false;
    }

    return mapData[y][x] != '#';
}

void Game::checkCollisions() {
    sf::FloatRect pacmanBounds = pacman.getSprite().getGlobalBounds();

    for (auto& point : GamePoints) {
        if (!point.isEaten() && pacmanBounds.intersects(point.getSprite().getGlobalBounds())) {
            int points = point.EatPoint();
            score.addPoints(points);
        }
    }

    for (auto& ghost : ghosts) {
        sf::FloatRect ghostBounds = ghost.getSprite().getGlobalBounds();
        if (pacmanBounds.intersects(ghostBounds)) {
            isRunning = false;
            std::cout << "Pacman został złapany przez ducha!" << std::endl;
        }
    }
}
