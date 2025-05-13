//
// Created by Cally on 4/7/2021.
//

#ifndef PROJECT_3_TEXTUREMANAGER_H
#define PROJECT_3_TEXTUREMANAGER_H

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

class TextureManager {

    static unordered_map<string, sf::Texture> textures;

public:

    static void LoadTexture(const string& textName);
    static sf::Texture& GetTexture(const string& textName);
    static sf::Texture LoadNum(const string& textName, int num);
    static void Clear();

};


#endif //PROJECT_3_TEXTUREMANAGER_H
