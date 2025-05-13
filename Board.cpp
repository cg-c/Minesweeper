//
// Created by Cally on 4/1/2021.
//

#include <iostream>
#include "Board.h"


Board::Board() {

    width = 25;
    height = 16;
    numMines = 50;
    tilesToUncover = (width * height) - numMines;

    CreateTiles();
    RandomizeMines();
    ConnectTiles();
    CheckNumMines();
    DisplayButtons();
    DisplayCounter();
}

Board::Board(int w, int h, int mines) {
    width = w;
    height = h;
    numMines = mines;
    tilesToUncover = (width * height) - numMines;

    CreateTiles();
    RandomizeMines();
    ConnectTiles();
    CheckNumMines();
    DisplayButtons();
    DisplayCounter();
}


Board::Board(vector<char> &mineVec) {
    width = 25;
    height = 16;
    numMines = 0;

    for (int i = 0; i < mineVec.size(); i++) {
        if (mineVec[i] == '1') {
            ++numMines;
        }
    }

    tilesToUncover = (width * height) - numMines;

    CreateTiles();
    IsMine(mineVec);
    ConnectTiles();
    CheckNumMines();
    DisplayButtons();
    DisplayCounter();
}


void Board::CreateTiles() {
    // load background, hidden sprite with textures
    for (int i = 0; i < width * height; i++) {

        Tile temp;

        int rowIndex = i / width;
        int columnIndex = i - (rowIndex * width);

        temp.background.move(columnIndex * 32, rowIndex * 32);
        temp.foreground.move(columnIndex * 32, rowIndex * 32);
        temp.object.move(columnIndex * 32, rowIndex * 32);

        temp.background.setTexture(TextureManager::GetTexture("tile_hidden"));
        temp.foreground.setTexture(TextureManager::GetTexture("tile_hidden"));
        tiles.push_back(temp);
    }
}


void Board::IsMine(vector<char> &mineVec) {
    for (int i = 0; i < mineVec.size(); i++) {
        if (mineVec[i] == '1') {
            tiles[i].isMine = true;
        }
    }
}


void Board::CheckNumMines() {

    for (int i = 0; i < tiles.size(); i++) {

        if (tiles[i].top != nullptr) {
            if (tiles[i].top->isMine) {
                tiles[i].neighborMines++;
            }
        }
        if (tiles[i].topLeft != nullptr) {
            if (tiles[i].topLeft->isMine) {
                tiles[i].neighborMines++;
            }
        }
        if (tiles[i].topRight != nullptr) {
            if (tiles[i].topRight->isMine) {
                tiles[i].neighborMines++;
            }
        }
        if (tiles[i].bottom != nullptr) {
            if (tiles[i].bottom->isMine) {
                tiles[i].neighborMines++;
            }
        }
        if (tiles[i].bottomLeft != nullptr) {
            if (tiles[i].bottomLeft->isMine) {
                tiles[i].neighborMines++;
            }
        }
        if (tiles[i].bottomRight != nullptr) {
            if (tiles[i].bottomRight->isMine) {
                tiles[i].neighborMines++;
            }
        }
        if (tiles[i].left != nullptr) {
            if (tiles[i].left->isMine) {
                tiles[i].neighborMines++;
            }
        }
        if (tiles[i].right != nullptr) {
            if(tiles[i].right->isMine) {
                tiles[i].neighborMines++;
            }
        }
    }
}


void Board::ConnectTiles() {

    Tile temp;

    for (int i = 0; i < width * height; i++) {

        if (i < width) {

            if (i % width == 0) {
                tiles[i].left = nullptr;
                tiles[i].bottomLeft = nullptr;
                tiles[i].right = &tiles[i + 1];
                tiles[i].bottomRight = &tiles[i + (width + 1)];
            }
            else if (i % width == width - 1) {
                tiles[i].right = nullptr;
                tiles[i].bottomRight = nullptr;
                tiles[i].left = &tiles[i - 1];
                tiles[i].bottomLeft = &tiles[i + (width - 1)];
            }
            else {
                tiles[i].bottomLeft = &tiles[i + (width - 1)];
                tiles[i].bottomRight = &tiles[i + (width + 1)];
                tiles[i].right = &tiles[i + 1];
                tiles[i].left = &tiles[i - 1];
            }

            tiles[i].bottom = &tiles[i + width];
            tiles[i].top = nullptr;
            tiles[i].topLeft = nullptr;
            tiles[i].topRight = nullptr;
        } // set all top neighbors to nullptr
        else if (i >= width *(height - 1)) {

            if (i % width == 0) {
                tiles[i].left = nullptr;
                tiles[i].topLeft = nullptr;
                tiles[i].right = &tiles[i + 1];
                tiles[i].topRight = &tiles[i - (width - 1)];
            }
            else if (i % width == width - 1) {
                tiles[i].right = nullptr;
                tiles[i].topRight = nullptr;
                tiles[i].left = &tiles[i - 1];
                tiles[i].topLeft = &tiles[i - (width + 1)];
            }
            else {
                tiles[i].right = &tiles[i + 1];
                tiles[i].left = &tiles[i - 1];
                tiles[i].topLeft = &tiles[i - (width + 1)];
                tiles[i].topRight = &tiles[i - (width - 1)];
            }

            tiles[i].top = &tiles[i - width];
            tiles[i].bottom = nullptr;
            tiles[i].bottomRight = nullptr;
            tiles[i].bottomLeft = nullptr;
        } // set all bottom to nullptr
        else if (i % width == 0) {

            tiles[i].right = &tiles[i + 1];
            tiles[i].left = nullptr;
            tiles[i].bottomLeft = nullptr;
            tiles[i].topLeft = nullptr;

            if (i < width) {
                tiles[i].top = nullptr;
                tiles[i].topRight = nullptr;
            }
            else if (i >= width *(height - 1)) {
                tiles[i].bottom = nullptr;
                tiles[i].bottomRight = nullptr;
            }
            else {
                tiles[i].top = &tiles[i - width];
                tiles[i].topRight = &tiles[i - (width - 1)];
                tiles[i].bottom = &tiles[i + width];
                tiles[i].bottomRight = &tiles[i + (width + 1)];
            }
        } // set all left to nullptr
        else if (i % width == width - 1) {

            tiles[i].left = &tiles[i - 1];
            tiles[i].right = nullptr;
            tiles[i].topRight = nullptr;
            tiles[i].bottomRight = nullptr;

            if (i < width) {
                tiles[i].top = nullptr;
                tiles[i].topLeft = nullptr;
                tiles[i].bottom = &tiles[i + width];
                tiles[i].bottomLeft = &tiles[i + (width - 1)];
            }
            else if (i >= width * (height - 1)) {
                tiles[i].bottom = nullptr;
                tiles[i].bottomLeft = nullptr;
                tiles[i].top = &tiles[i - width];
                tiles[i].topLeft = &tiles[i - (width + 1)];
            }
            else {
                tiles[i].top = &tiles[i - width];
                tiles[i].bottom = &tiles[i + width];
                tiles[i].topLeft = &tiles[i - (width + 1)];
                tiles[i].bottomLeft = &tiles[i + (width - 1)];
            }
        } // set all right to nullptr
        else {
            tiles[i].top = &tiles[i - width];
            tiles[i].topLeft = &tiles[i - (width + 1)];
            tiles[i].topRight = &tiles[i - (width - 1)];
            tiles[i].bottom = &tiles[i + width];
            tiles[i].bottomLeft = &tiles[i + (width - 1)];
            tiles[i].bottomRight = &tiles[i + (width + 1)];
            tiles[i].right = &tiles[i + 1];
            tiles[i].left = &tiles[i - 1];
        }
    }
}


void Board::DisplayButtons() {

    int cIndex = height * 32;
    int wIndex = (width / 2) * 32;

    face.setTexture(TextureManager::GetTexture("face_happy"));
    face.move( wIndex, cIndex);

    debug.setTexture(TextureManager::GetTexture(("debug")));
    debug.move(wIndex + (4 * 32), cIndex);

    test1.setTexture(TextureManager::GetTexture("test_1"));
    test1.move(wIndex + (6 * 32), cIndex);
    test2.setTexture(TextureManager::GetTexture("test_2"));
    test2.move(wIndex + (8 * 32), cIndex);
    test3.setTexture(TextureManager::GetTexture("test_3"));
    test3.move(wIndex + (10 * 32), cIndex);
}


void Board::TileReveal(int index) {

    if (tiles[index].isHidden) {

        tiles[index].isHidden = false;

        if (tiles[index].isMine) {
            tiles[index].foreground.setTexture(TextureManager::GetTexture("mine"));
            tiles[index].background.setTexture(TextureManager::GetTexture("tile_revealed"));
            return;
        }
        else if (tiles[index].neighborMines == 1) {
            tiles[index].object.setTexture(TextureManager::GetTexture("number_1"));
            tiles[index].foreground.setTexture(TextureManager::GetTexture("number_1"));
        }
        else if (tiles[index].neighborMines == 2) {
            tiles[index].object.setTexture(TextureManager::GetTexture("number_2"));
            tiles[index].foreground.setTexture(TextureManager::GetTexture("number_2"));
        }
        else if (tiles[index].neighborMines == 3) {
            tiles[index].object.setTexture(TextureManager::GetTexture("number_3"));
            tiles[index].foreground.setTexture(TextureManager::GetTexture("number_3"));
        }
        else if (tiles[index].neighborMines == 4) {
            tiles[index].object.setTexture(TextureManager::GetTexture("number_4"));
            tiles[index].foreground.setTexture(TextureManager::GetTexture("number_4"));
        }
        else if (tiles[index].neighborMines == 5) {
            tiles[index].object.setTexture(TextureManager::GetTexture("number_5"));
            tiles[index].foreground.setTexture(TextureManager::GetTexture("number_5"));
        }
        else if (tiles[index].neighborMines == 6) {
            tiles[index].object.setTexture(TextureManager::GetTexture("number_6"));
            tiles[index].foreground.setTexture(TextureManager::GetTexture("number_6"));
        }
        else if (tiles[index].neighborMines == 7) {
            tiles[index].object.setTexture(TextureManager::GetTexture("number_7"));
            tiles[index].foreground.setTexture(TextureManager::GetTexture("number_7"));
        }
        else if (tiles[index].neighborMines == 8) {
            tiles[index].object.setTexture(TextureManager::GetTexture("number_8"));
            tiles[index].foreground.setTexture(TextureManager::GetTexture("number_8"));
        }
        else if (tiles[index].neighborMines == 0) {
            tiles[index].object.setTexture(TextureManager::GetTexture("tile_revealed"));
            tiles[index].foreground.setTexture(TextureManager::GetTexture("tile_revealed"));
        }

        tiles[index].background.setTexture(TextureManager::GetTexture("tile_revealed"));
        --tilesToUncover;
    }
}


void Board::DisplayCounter() {

    int cIndex = height * 32;
    int wIndex = 21;

    counter1.move(wIndex, cIndex);
    counter1.setTexture(TextureManager::GetTexture("digits"));
    counter1.setTextureRect(sf::IntRect(0, 0, 21, 32));

    counter2.move(wIndex + 21, cIndex);
    counter2.setTexture(TextureManager::GetTexture("digits"));
    counter2.setTextureRect(sf::IntRect(0, 0, 21, 32));

    counter3.move(wIndex + 42, cIndex);
    counter3.setTexture(TextureManager::GetTexture("digits"));
    counter3.setTextureRect(sf::IntRect(0, 0, 21, 32));

    counter4.move(0, cIndex);
    counter4.setTexture(TextureManager::GetTexture("digits"));
    counter4.setTextureRect(sf::IntRect((10 * 21), 0,  21, 32));
}


Board::~Board() {
    tiles.clear();
}


void Board::RandomizeMines() {

    int numMinesGen = 0;
    int x;

    while (numMinesGen != numMines) {

        for (int i = 0; i < tiles.size(); i++) {

            x = Random::Int(0, 25);

            if (tiles[i].isMine) {
                //nothing
            }
            else if (x == 1) {
                ++numMinesGen;
                tiles[i].isMine = true;
            }

            if (numMinesGen == numMines) {
                break;
            }
        }
    }
}


void Board::Recursion(int index) {

    if (tiles[index].neighborMines == 0 && !tiles[index].isMine && !tiles[index].isFlag && tiles[index].isHidden) {

        TileReveal(index);

        if (tiles[index].top != nullptr && !tiles[index].top->isFlag && !tiles[index].top->isMine && tiles[index].top->isHidden) {
            Recursion(index - width);
            TileReveal(index - width);
        }
        if (tiles[index].topLeft != nullptr && !tiles[index].topLeft->isFlag && !tiles[index].topLeft->isMine && tiles[index].topLeft->isHidden) {
            Recursion(index - (width + 1));
            TileReveal(index - (width + 1));
        }
        if (tiles[index].topRight != nullptr && !tiles[index].topRight->isFlag && !tiles[index].topRight->isMine && tiles[index].topRight->isHidden) {
            Recursion(index - (width - 1));
            TileReveal(index - (width - 1));
        }
        if (tiles[index].bottom != nullptr && !tiles[index].bottom->isFlag && !tiles[index].bottom->isMine && tiles[index].bottom->isHidden) {
            Recursion(index + width);
            TileReveal(index + width);
        }
        if (tiles[index].bottomLeft != nullptr && !tiles[index].bottomLeft->isFlag && !tiles[index].bottomLeft->isMine && tiles[index].bottomLeft->isHidden) {
            Recursion(index + (width - 1));
            TileReveal(index + (width - 1));
        }
        if (tiles[index].bottomRight != nullptr && !tiles[index].bottomRight->isFlag && !tiles[index].bottomRight->isMine && tiles[index].bottomRight->isHidden) {
            Recursion(index + (width + 1));
            TileReveal(index + (width + 1));
        }
        if (tiles[index].left != nullptr && !tiles[index].left->isFlag && !tiles[index].left->isMine && tiles[index].left->isHidden) {
            Recursion(index - 1);
            TileReveal(index - 1);
        }
        if (tiles[index].right != nullptr && !tiles[index].right->isFlag && !tiles[index].right->isMine && tiles[index].right->isHidden) {
            Recursion(index + 1);
            TileReveal(index + 1);
        }
    }
    else if (!tiles[index].isMine && !tiles[index].isFlag && tiles[index].isHidden) {
        TileReveal(index);
    }
}

