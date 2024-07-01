/**
 * @file Keyboard.h
 * @brief A file containing a class with the same name
 */
#ifndef HANGMAN_KEYBOARD_H
#define HANGMAN_KEYBOARD_H
#include "Gui.h"

/**
 * @class Keyboard
 * @brief Class reponsible for drawing keyboard
 */
class Keyboard {
private:
    std::map<uint8_t, gui::Button*> buttons; ///<A vector that stores all buttons
    sf::Font font; ///<Font reference requiered to render text.
    class GraphicsSettings* gfxSettings; ///<Pointer to the graphics settings

    /**
    * @brief Function creating all buttons and their views.
    */
    void initKeyboard();
public:
    /**
    * @brief Class constructor
    */
    Keyboard(const sf::Font& font, GraphicsSettings* settings);

    /**
    * @brief Class destructor
    */
    virtual ~Keyboard();

    /**
    * @brief Setting button availability to locked or unlocked
    * @param key ID
    * @param enabled Should be enabled or not
    */
    void SetButtonEnabled(uint8_t key,bool enabled);

    /**
    * @brief Setting button color
    * @param key ID
    * @param color Color to be set
    */
    void SetButtonColor(uint8_t key,sf::Color color);

    /**
    * @brief Checking if button is pressed
    * @param Key ID
    * @returns Returns state of the button
    */
    bool IsPressed(uint8_t key);
    /**
    * @brief Updating buttons functionality
    * @param dt Delta time
    */
    void updateButtons(const sf::Vector2i& mousePosWindow,const float& dt);

    /**
    * @brief Module loop updating events
    * @param dt Delta time value
    */
    void update(const sf::Vector2i& mousePosWindow,const float& dt);

    /**
    * @brief Module loop for rendering
    * @param target Pointer to the renderer
    */
    void render(sf::RenderTarget* target = nullptr);
};


#endif
