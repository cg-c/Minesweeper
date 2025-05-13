#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include "TextureManager.h"
#include "Board.h"
#include "GameManager.h"

using namespace std;

void ReadConfig(string &sNumMines, string &sWidth, string &sHeight);
void ReadTestBoard(string &path, vector<char> &mineVec);


int main() {

    TextureManager::LoadTexture("tile_hidden");
    TextureManager::LoadTexture("tile_revealed");
    TextureManager::LoadTexture("mine");
    TextureManager::LoadTexture("flag");
    TextureManager::LoadTexture("debug");
    TextureManager::LoadTexture("test_1");
    TextureManager::LoadTexture("test_2");
    TextureManager::LoadTexture("test_3");
    TextureManager::LoadTexture("face_happy");
    TextureManager::LoadTexture("face_lose");
    TextureManager::LoadTexture("face_win");
    TextureManager::LoadTexture("digits");
    TextureManager::LoadTexture("number_1");
    TextureManager::LoadTexture("number_2");
    TextureManager::LoadTexture("number_3");
    TextureManager::LoadTexture("number_4");
    TextureManager::LoadTexture("number_5");
    TextureManager::LoadTexture("number_6");
    TextureManager::LoadTexture("number_7");
    TextureManager::LoadTexture("number_8");

    string sHeight;
    string sWidth;
    string sNumMines;
    int height;
    int width;
    int numMines;
    int leftClick;
    int x;
    int y;

    ReadConfig(sNumMines, sWidth, sHeight);
    height = stoi(sHeight);
    width = stoi(sWidth);
    numMines = stoi(sNumMines);
    GameManager *gameManager = new GameManager(width, height, numMines);

    sf::RenderWindow window(sf::VideoMode(width * 32, (height * 32) + 88), "Minesweeper");

    while (window.isOpen()) {

        sf::Event event;
        vector<char> mineVec;

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {

                x = event.mouseButton.x;
                y = event.mouseButton.y;

                if (event.mouseButton.button == sf::Mouse::Left) {

                    leftClick = gameManager->LeftClick(x, y);

                    if (leftClick == 1) {
                        string path = "testboard1.brd";
                        ReadTestBoard(path, mineVec);
                        delete gameManager;
                        gameManager = new GameManager(mineVec);
                    }
                    else if (leftClick == 2) {
                        string path = "testboard2.brd";
                        ReadTestBoard(path, mineVec);
                        delete gameManager;
                        gameManager = new GameManager(mineVec);
                    }
                    else if (leftClick == 3) {
                        string path = "testboard3.brd";
                        ReadTestBoard(path, mineVec);
                        delete gameManager;
                        gameManager = new GameManager(mineVec);
                    }
                    else if (leftClick == 4) {
                        delete gameManager;
                        gameManager = new GameManager(width, height, numMines);
                    }
                    else if (leftClick == 5) {
                        gameManager->Debug();
                    }
                }
                else if (event.mouseButton.button == sf::Mouse::Right) {
                    gameManager->RightClick(x, y);
                }
            }
        }

        window.clear(sf::Color::White);
        gameManager->GenerateBoard(window);
        window.display();
    }
    TextureManager::Clear();
    return 0;
}


void ReadConfig(string &sNumMines, string &sWidth, string &sHeight) {

    fstream file;

    file.open("boards/config.cfg");

    if (file.is_open()) {
        getline(file, sWidth);
        getline(file, sHeight);
        getline(file, sNumMines);
    }
}


void ReadTestBoard(string &path, vector<char> &mineVec) {

    ifstream file;
    char num;
    path = "boards/" + path;

    file.open(path);

    if (file.is_open()) {

        while(!file.eof()) {

            file.get(num);

            if (!isdigit(num)) {
                file.get(num);
            }
            mineVec.push_back(num);
        }
    }
}
