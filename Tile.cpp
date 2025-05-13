//
// Created by Cally on 4/1/2021.
//

#include "Tile.h"

Tile::Tile() {
    top = nullptr;
    bottom = nullptr;
    left = nullptr;
    right = nullptr;
    topLeft = nullptr;
    topRight = nullptr;
    bottomLeft = nullptr;
    bottomRight = nullptr;

    neighborMines = 0;
    isMine = false;
    isFlag = false;
    isHidden = true;
}


Tile::~Tile() {
    top = nullptr;
    bottom = nullptr;
    left = nullptr;
    right = nullptr;
    topLeft = nullptr;
    topRight = nullptr;
    bottomLeft = nullptr;
    bottomRight = nullptr;
}
