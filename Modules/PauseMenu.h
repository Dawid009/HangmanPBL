/**
 * @file PauseMenu.h
 * @brief In-game pause menu
 */

#ifndef HANGMAN_PAUSESCREEN_H
#define HANGMAN_PAUSESCREEN_H

#include"Gui.h"

class Gui;


/**
 * @class PauseMenu
 * @brief Class reponsible for in-game menu
 */
class PauseMenu
{
private:
    sf::Font& font; ///<Pointer to the font
    sf::Text menuText; ///<Menu text object
    sf::RectangleShape background; ///<Background object
    sf::RectangleShape container; ///<Container
    std::map<std::string, gui::Button*> buttons; ///<A map that stores the buttons

public:
    /**
    * @brief Class constructor
    * @param vm Video Mode
    * @param font Pointer to the font
    */
    PauseMenu(sf::VideoMode& vm, sf::Font& font);

    /**
    * @brief Class destructor
    */
    virtual ~PauseMenu();

    /**
    * @brief Check if button is pressed
    * @param key Key of the button
    * @return Return value of true or false
    */
    bool isButtonPressed(const std::string& key);

    /**
    * @brief Creates new button
    * @param key Key of the button
    * @param y Y position
    * @param width Width of the button
    * @param height Height of the button
    * @param char_size Character size
    * @param text Text ref to display
    */
    void addButton(const std::string& key,
                   const float y,
                   const float width,
                   const float height,
                   const unsigned char_size,
                   const std::wstring& text);

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
