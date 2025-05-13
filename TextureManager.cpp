//
// Created by Cally on 4/7/2021.
//

#include "TextureManager.h"

unordered_map<string, sf::Texture> TextureManager::textures;


void TextureManager::LoadTexture(const string& textName) {

    string path = "images/";
    path += textName + ".png";

    textures[textName].loadFromFile(path);
}

sf::Texture &TextureManager::GetTexture(const string& textName) {

    if (textures.find(textName) == textures.end()) {
        LoadTexture(textName);
    }

    return textures[textName];
}

void TextureManager::Clear() {
    textures.clear();
}

sf::Texture TextureManager::LoadNum(const string& textName, int num) {
    sf::Texture digit = GetTexture(textName);
    digit.loadFromFile("image/" + textName + ".png", sf::IntRect(num * 21, 0, (num * 21) + 21, 32));
    return digit;
}
