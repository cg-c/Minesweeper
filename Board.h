//
// Created by Cally on 4/1/2021.
//

#ifndef PROJECT_3_BOARD_H
#define PROJECT_3_BOARD_H

#include <vector>
#include <string>
#include <fstream>
#include "Tile.h"
#include "TextureManager.h"
#include "Random.h"

using namespace std;

class Board {

public:

    vector<Tile> tiles;
    ifstream file;
    int width;
    int height;
    int numMines;
    int tilesToUncover;
    sf::Sprite face;
    sf::Sprite debug;
    sf::Sprite test1;
    sf::Sprite test2;
    sf::Sprite test3;
    sf::Sprite counter1;
    sf::Sprite counter2;
    sf::Sprite counter3;
    sf::Sprite counter4;


    Board();
    Board(int w, int h, int mines);
    Board(vector<char> &mineVec);
    ~Board();

    void ConnectTiles();
    void CreateTiles();
    void IsMine(vector<char> &mineVec);
    void CheckNumMines();
    void DisplayButtons();
    void TileReveal(int index);
    void DisplayCounter();
    void Recursion(int index);
    void RandomizeMines();
};


#endif //PROJECT_3_BOARD_H
