//
// Created by Cally on 4/1/2021.
//

#ifndef PROJECT_3_TILE_H
#define PROJECT_3_TILE_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "TextureManager.h"


using namespace std;

struct Tile {

    sf::Sprite background;
    sf::Sprite foreground;
    sf::Sprite object;

    Tile* top;
    Tile* bottom;
    Tile* left;
    Tile* right;
    Tile* topLeft;
    Tile* topRight;
    Tile* bottomLeft;
    Tile* bottomRight;

    bool isMine;
    bool isFlag;
    bool isHidden;

    int neighborMines;

    Tile();
    ~Tile();
};


#endif //PROJECT_3_TILE_H
