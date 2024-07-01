/**
 * @file EndScreen.h
 * @brief In-game end screen overlay
 */

#ifndef HANGMAN_ENDSCREEN_H
#define HANGMAN_ENDSCREEN_H

#include"Gui.h"
#include "SaveGame.h"

class Gui;
/**
 * @class EndScreen
 * @brief Class reponsible for End screen overlay
 */
class EndScreen
{
private:
    SaveGame* saveGame; ///<Savegame pointer
    sf::Font& font; ///<Pointer to the font
    sf::Text menuText; ///<Menu text object
    sf::RectangleShape background; ///<Background object
    sf::RectangleShape container; ///<Container
    std::map<std::string, gui::Button*> buttons; ///<A map that stores the buttons
    sf::Text winText; ///<Win text object pointer
    sf::Text loseText;///<Lose text object pointer
    bool win=false; ///<Is game win?

public:
    /**
    * @brief Class constructor
    * @param vm Video Mode
    * @param font Pointer to the font
    */
    EndScreen(sf::VideoMode& vm, sf::Font& font);

    /**
    * @brief Class destructor
    */
    virtual ~EndScreen();

    /**
    * @brief Check if button is pressed
    * @param key Key of the button
    * @return Return value of true or false
    */
    bool isButtonPressed(const std::string& key);

    /**
    * @brief Function setting this object to win or not
    * @param iswin Bool is win or not
    */
    void setWin(bool iswin) {this->win = iswin;};

    /**
    * @brief Main state loop updating events
    * @param dt Delta time value
    */
    void update(const sf::Vector2i& mousePosWindow,const float& dt);

    /**
    * @brief Loop for rendering
    * @param target Pointer to the renderer
    */
    void render(sf::RenderTarget& target);
};



#endif
