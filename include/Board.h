#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "point.h"

class Board {
public:
    Board(const std::string &_path);
    void setMap(const std::string &mapStructure);
    const std::vector<sf::Sprite>& getSprites() const;
    sf::Vector2u getSize() const;
    const std::vector<point>& getPoints() const;
    std::vector<sf::Vector2u> getEntityPos() const;
    std::vector<std::string>& getMapData();

private:
    std::vector<sf::Texture> mapTextures;
    std::vector<sf::Sprite> mapSprites;
    std::vector<point> points;
    std::vector<sf::Vector2u> entityPos;
    std::vector<std::string> mapData;
    sf::Texture pointTexture;
    sf::Vector2u mapSize;
};

#endif // BOARD_H
