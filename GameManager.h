//
// Created by Cally on 4/1/2021.
//

#ifndef PROJECT_3_GAMEMANAGER_H
#define PROJECT_3_GAMEMANAGER_H

#include "Board.h"
#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>


class GameManager {

    int width;
    int height;
    int numMines;
    bool gameOver;
    bool lose;
    bool debugMode;
    int minesToFlag;
    bool negCounter;

    void SetNumOfCounter(char &c, sf::Sprite &sprite);

public:

    GameManager();
    GameManager(int w, int h, int mines);
    GameManager(vector<char> &mineVec);
    ~GameManager();

    Board* board;

    void GenerateBoard(sf::RenderWindow &window);
    int LeftClick(int x, int y);
    void RightClick(int x, int y);
    void Lost();
    void Win();
    void SetCounter();
    void Debug();
};


#endif //PROJECT_3_GAMEMANAGER_H
