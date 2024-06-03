/**
 * @file GraphicsSettings.h
 * @brief Graphics settings reading and saving to file
 */

#ifndef HANGMAN_GRAPHICSSETTINGS_H
#define HANGMAN_GRAPHICSSETTINGS_H
#include <iostream>
#include "SFML/Graphics.hpp"

/**
* @class GraphicsSettings
* @brief Class reading and saving settings
*/
class GraphicsSettings {
public:
    /**
    * @brief Class constructor
    */
    GraphicsSettings();

    std::string title; ///<Window title
    sf::VideoMode resolution;///<Window resolution
    bool fullscreen;///<Should the game be in fullscreen
    bool verticalSync;///<Should the game use vertical sync
    bool showFps;
    unsigned frameRateLimit;///<FPS cap
    sf::ContextSettings contextSettings; ///<
    std::vector<sf::VideoMode> videoModes; ///<array of all resolutions

    /**
    * @brief Saving settings to file
    * @param path Path to graphics.ini file
    */
    void saveToFile(const std::string& path) const;
    /**
    * @brief Reading settings from file
    * @param path Path to graphics.ini file
    */
    void loadFromFile(const std::string& path);
};

#endif //HANGMAN_GRAPHICSSETTINGS_H
