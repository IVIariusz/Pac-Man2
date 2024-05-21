#include <fstream>
#include <vector>
#include "../include/Board.h"
#include "../include/setting.h"
#include "../include/point.h"
#include <iostream>

Board::Board(const std::string &_path) {
    sf::Texture mapTexture;
    if (!mapTexture.loadFromFile(_path)) {
        throw std::runtime_error("Nie można załadować tekstury z pliku: " + _path);
    }
    int width = mapTexture.getSize().x / ASSETS_SIZE;
    int height = mapTexture.getSize().y / ASSETS_SIZE;

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            sf::Texture temp;
            temp.loadFromImage(mapTexture.copyToImage(), sf::IntRect(32 * i, 32 * j, 32, 32));
            mapTextures.push_back(temp);
        }
    }

    if (!pointTexture.loadFromFile(ASSET_POINT)) {
        throw std::runtime_error("Nie można załadować tekstury z pliku: " + std::string(ASSET_POINT));
    }

    setMap(MAP_STRUCTURE);
}

void Board::setMap(const std::string &mapStructure) {
    std::ifstream mapFile(mapStructure);
    if (!mapFile) {
        throw std::runtime_error("Nie można otworzyć pliku mapy: " + mapStructure);
    }

    std::string line;
    while (std::getline(mapFile, line)) {
        mapData.push_back(line);
    }

    mapSize = sf::Vector2u(mapData[0].size() * ASSETS_SIZE, mapData.size() * ASSETS_SIZE);

    int textureID, i, j;

    for (i = 0; i < mapData.size(); ++i) {
        for (j = 0; j < mapData[i].length(); ++j) {
            textureID = 0;
            if (mapData[i][j] != '#') {
                if (i > 0 && mapData[i-1][j] == '#') textureID += 1; // Góra
                if (i+1 < mapData.size() && mapData[i+1][j] == '#') textureID += 2; // Dół
                if (j > 0 && mapData[i][j-1] == '#') textureID += 4; // Lewo
                if (j+1 < mapData[i].length() && mapData[i][j+1] == '#') textureID += 8; // Prawo

                int tempId = 0;
                switch (textureID) {
                    case 13: tempId = 1; break;
                    case 12: tempId = 2; break;
                    case 14: tempId = 3; break;
                    case 15: tempId = 4; break;
                    case 7: tempId = 5; break;
                    case 5: tempId = 6; break;
                    case 6: tempId = 7; break;
                    case 3: tempId = 9; break;
                    case 9: tempId = 10; break;
                    case 10: tempId = 11; break;
                    case 11: tempId = 13; break;
                    case 4: tempId = 14; break;
                    case 8: tempId = 20; break;
                    case 1: tempId = 18; break;
                    case 2: tempId = 15; break;
                    default: tempId = 19; break; // Default textureID
                }

                sf::Sprite sprite;
                sprite.setTexture(mapTextures[tempId - 1]);
                sprite.setPosition(j * ASSETS_SIZE, i * ASSETS_SIZE);
                mapSprites.push_back(sprite);
            } else {
                sf::Sprite sprite;
                sprite.setTexture(mapTextures[15]); // Default texture for '#'
                sprite.setPosition(j * ASSETS_SIZE, i * ASSETS_SIZE);
                mapSprites.push_back(sprite);
            }
            if (mapData[i][j] == '.') {
                point _point;
                _point.setPoint(pointTexture, sf::Vector2u(j * ASSETS_SIZE + 0.4 * ASSETS_SIZE, i * ASSETS_SIZE + 0.4 * ASSETS_SIZE), 1);
                points.push_back(_point);
            } else if (mapData[i][j] == 'o') {
                point _point;
                _point.setPoint(pointTexture, sf::Vector2u(j * ASSETS_SIZE + 0.2 * ASSETS_SIZE, i * ASSETS_SIZE + 0.2 * ASSETS_SIZE), 2);
                points.push_back(_point);
            } else if (mapData[i][j] == '0') {
                std::cout << "0";
                sf::Vector2u pos(j * ASSETS_SIZE + 0.2 * ASSETS_SIZE, i * ASSETS_SIZE + 0.2 * ASSETS_SIZE);
                entityPos.push_back(pos);
            } else if (mapData[i][j] == '1') {
                std::cout << "1";
                sf::Vector2u pos(j * ASSETS_SIZE + 0.2 * ASSETS_SIZE, i * ASSETS_SIZE + 0.2 * ASSETS_SIZE);
                entityPos.push_back(pos);
            } else if (mapData[i][j] == '2') {
                std::cout << "2";
                sf::Vector2u pos(j * ASSETS_SIZE + 0.2 * ASSETS_SIZE, i * ASSETS_SIZE + 0.2 * ASSETS_SIZE);
                entityPos.push_back(pos);
            } else if (mapData[i][j] == '3') {
                std::cout << "3";
                sf::Vector2u pos(j * ASSETS_SIZE + 0.2 * ASSETS_SIZE, i * ASSETS_SIZE + 0.2 * ASSETS_SIZE);
                entityPos.push_back(pos);
            } else if (mapData[i][j] == '4') {
                std::cout << "4";
                sf::Vector2u pos(j * ASSETS_SIZE + 0.2 * ASSETS_SIZE, i * ASSETS_SIZE + 0.2 * ASSETS_SIZE);
                entityPos.push_back(pos);
            }
        }
    }
}

const std::vector<sf::Sprite>& Board::getSprites() const {
    return mapSprites;
}

sf::Vector2u Board::getSize() const {
    return mapSize;
}

const std::vector<point>& Board::getPoints() const {
    return points;
}

std::vector<sf::Vector2u> Board::getEntityPos() const {
    return entityPos;
}

std::vector<std::string>& Board::getMapData() {
    return mapData;
}