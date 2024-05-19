#ifndef HANGMAN_GRAPHICSSETTINGS_H
#define HANGMAN_GRAPHICSSETTINGS_H
#include <iostream>
#include "SFML/Graphics.hpp"

class GraphicsSettings {
public:
    GraphicsSettings();

    //Zmienne
    std::string title;
    sf::VideoMode resolution;
    bool fullscreen;
    bool verticalSync;
    unsigned frameRateLimit;
    sf::ContextSettings contextSettings;
    std::vector<sf::VideoMode> videoModes;

    //Funkcje
    void saveToFile(const std::string path);
    void loadFromFile(const std::string path);
};


#endif //HANGMAN_GRAPHICSSETTINGS_H
