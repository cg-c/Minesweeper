//
// Created by Cally on 4/1/2021.
//

#include "GameManager.h"

GameManager::GameManager() {
    negCounter = false;
    debugMode = false;
    gameOver = false;
    lose = false;
    width = 25;
    height = 16;
    numMines = 50;
    minesToFlag = numMines;
    board = new Board(width, height, 50);
}

GameManager::GameManager(int w, int h, int mines) {
    negCounter = false;
    debugMode = false;
    gameOver = false;
    lose = false;
    width = w;
    height = h;
    numMines = mines;
    minesToFlag = numMines;
    board = new Board(width, height, mines);
}


GameManager::GameManager(vector<char> &mineVec) {
    negCounter = false;
    debugMode = false;
    gameOver = false;
    lose = false;
    width = 25;
    height = 16;
    board = new Board(mineVec);
    numMines = board->numMines;
    minesToFlag = numMines;
}


void GameManager::GenerateBoard(sf::RenderWindow &window) {

    for (int i = 0; i < width * height; i++) {

        window.draw(board->tiles[i].background);
        window.draw(board->tiles[i].foreground);

        if (debugMode) {
            window.draw(board->tiles[i].object);
        }

        if (lose ) {
            window.draw(board->tiles[i].object);
        }

        SetCounter();

        window.draw(board->face);
        window.draw(board->debug);
        window.draw(board->test1);
        window.draw(board->test2);
        window.draw(board->test3);
        window.draw(board->counter1);
        window.draw(board->counter2);
        window.draw(board->counter3);

        if (negCounter) {
            window.draw(board->counter4);
        }
    }
}


GameManager::~GameManager() {
    delete board;
    board = nullptr;
}


int GameManager::LeftClick(int x, int y) {

    if (!gameOver) {
        for (int i = 0; i < board->tiles.size(); i++) {

            if (board->tiles[i].foreground.getGlobalBounds().contains(x, y)) {

                if (board->tiles[i].isFlag) {
                    return 0;
                }
                else if (board->tiles[i].isHidden) {

                    if (board->tiles[i].isMine) {
                        lose = true;
                        gameOver = true;
                        Lost();
                        return 0;
                    }

                    board->Recursion(i);

                    if (board->tilesToUncover == 0) {
                        gameOver = true;
                        Win();
                    }
                    return 0;
                }
            }
        }
    }

    if (board->debug.getGlobalBounds().contains(x, y) && !gameOver) {
        debugMode = !debugMode;
        return 5;
    }
    else if (board->face.getGlobalBounds().contains(x, y)) {
        return 4;
    }
    else if (board->test1.getGlobalBounds().contains(x, y)) {
        return 1;
    }
    else if (board->test2.getGlobalBounds().contains(x, y)) {
        return 2;
    }
    else if (board->test3.getGlobalBounds().contains(x, y)) {
        return 3;
    }
    return 0;
}


void GameManager::RightClick(int x, int y) {

    if (!gameOver) {

        for (int i = 0; i < board->tiles.size(); i++) {

            if (board->tiles[i].foreground.getGlobalBounds().contains(x, y)) {

                if (!debugMode) {

                    if (board->tiles[i].isHidden && !board->tiles[i].isFlag) {
                        board->tiles[i].foreground.setTexture(TextureManager::GetTexture("flag"));
                        board->tiles[i].isFlag = true;
                        --minesToFlag;
                        return;
                    }
                    else if (board->tiles[i].isFlag) {
                        board->tiles[i].isFlag = false;
                        board->tiles[i].foreground.setTexture(TextureManager::GetTexture("tile_hidden"));
                        ++minesToFlag;
                        return;
                    }
                }
                else {

                    if (board->tiles[i].isHidden && !board->tiles[i].isFlag) {
                        board->tiles[i].foreground.setTexture(TextureManager::GetTexture("flag"));
                        board->tiles[i].background.setTexture(TextureManager::GetTexture("tile_hidden"));
                        board->tiles[i].isFlag = true;
                        --minesToFlag;
                        return;
                    }
                    else if (board->tiles[i].isFlag) {
                        board->tiles[i].isFlag = false;
                        board->tiles[i].foreground.setTexture(TextureManager::GetTexture("tile_hidden"));
                        board->tiles[i].background.setTexture(TextureManager::GetTexture("tile_revealed"));
                        ++minesToFlag;
                        return;
                    }
                }
            }
        }
    }
}


void GameManager::Debug() {

    for (int i = 0; i < board->tiles.size(); i++) {

        if (board->tiles[i].isMine) {

            if (debugMode) {

                if (board->tiles[i].isFlag) {
                    board->tiles[i].foreground.setTexture(TextureManager::GetTexture("flag"));
                    board->tiles[i].background.setTexture(TextureManager::GetTexture("tile_hidden"));
                }
                board->tiles[i].object.setTexture(TextureManager::GetTexture("mine"));
            }
            else {

                if (board->tiles[i].isFlag) {
                    board->tiles[i].foreground.setTexture(TextureManager::GetTexture("flag"));
                }
                board->tiles[i].background.setTexture(TextureManager::GetTexture("tile_hidden"));
            }
        }
        else if (board->tiles[i].isFlag) {
            board->tiles[i].foreground.setTexture(TextureManager::GetTexture("flag"));
            board->tiles[i].background.setTexture(TextureManager::GetTexture("tile_hidden"));
        }
    }
}


void GameManager::Lost() {

    board->face.setTexture(TextureManager::GetTexture("face_lose"));

    for (int i = 0; i < board->tiles.size(); i++) {

        if (board->tiles[i].isMine) {
            board->TileReveal(i);

            if (board->tiles[i].isFlag) {
                board->tiles[i].object.setTexture(TextureManager::GetTexture("mine"));
                board->tiles[i].foreground.setTexture(TextureManager::GetTexture("flag"));
                board->tiles[i].background.setTexture(TextureManager::GetTexture("tile_revealed"));
            }
        }
    }
}


void GameManager::Win() {

    board->face.setTexture(TextureManager::GetTexture("face_win"));
    minesToFlag = 0;

    for (int i = 0; i < board->tiles.size(); i++) {

        if (board->tiles[i].isMine) {
            board->tiles[i].foreground.setTexture(TextureManager::GetTexture("flag"));
            board->tiles[i].background.setTexture(TextureManager::GetTexture("tile_hidden"));
        }
    }
}


void GameManager::SetCounter() {

    string mines = to_string(minesToFlag);

    if (mines.at(0) == '-') {

        negCounter = true;

        while (mines.length() < 4) {
            mines.insert(1, "0");
        }

        SetNumOfCounter(mines.at(1), board->counter1);
        SetNumOfCounter(mines.at(2), board->counter2);
        SetNumOfCounter(mines.at(3), board->counter3);
    }
    else {

        while (mines.length() < 3) {
            mines = "0" + mines;
        }

        negCounter = false;

        SetNumOfCounter(mines.at(0), board->counter1);
        SetNumOfCounter(mines.at(1), board->counter2);
        SetNumOfCounter(mines.at(2), board->counter3);
    }
}


void GameManager::SetNumOfCounter(char &c, sf::Sprite &sprite) {

    if (c == '1') {
        sprite.setTextureRect(sf::IntRect((1 * 21), 0, 21, 32));
    }
    else if (c == '2') {
        sprite.setTextureRect(sf::IntRect((2 * 21), 0, 21, 32));
    }
    else if (c == '3') {
        sprite.setTextureRect(sf::IntRect((3 * 21), 0, 21, 32));
    }
    else if (c == '4') {
        sprite.setTextureRect(sf::IntRect((4 * 21), 0, 21, 32));
    }
    else if (c == '5') {
        sprite.setTextureRect(sf::IntRect((5 * 21), 0, 21, 32));
    }
    else if (c == '6') {
        sprite.setTextureRect(sf::IntRect((6 * 21), 0, 21, 32));
    }
    else if (c == '7') {
        sprite.setTextureRect(sf::IntRect((7 * 21), 0, 21, 32));
    }
    else if (c == '8') {
        sprite.setTextureRect(sf::IntRect((8 * 21), 0, 21, 32));
    }
    else if (c == '9') {
        sprite.setTextureRect(sf::IntRect((9 * 21), 0, 21, 32));
    }
    else if (c == '0') {
        sprite.setTextureRect(sf::IntRect(0, 0, 21, 32));
    }
}

