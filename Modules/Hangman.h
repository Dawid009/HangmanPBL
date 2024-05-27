/**
 * @file Hangman.h
 * @brief A file containing a class with the same name
 */
#ifndef HANGMAN_HANGMAN_H
#define HANGMAN_HANGMAN_H
#include "Gui.h"

/**
 * @class Hangman
 * @brief Class reponsible for drawing hangman
 */
class Hangman {

private:
    class GraphicsSettings* gfxSettings; ///<Pointer to graphics settings
    sf::RenderTexture* renderTexture; ///<Texture storing a view of the entire hangman
    sf::Sprite* sprite; ///<Sprite needed to display hangman on the screen
    sf::RectangleShape* line; ///<Line object pointer
    sf::Shape* hangman_parts[6]; ///<Pointers to parts of the body

    void initHangman();
public:

    /**
    * @brief Class constructor
    * @param settings Pointer to the main graphics settings
    */
    Hangman(GraphicsSettings *settings);

    /**
    * @brief Class destructor
    */
    virtual ~Hangman();

    /**
    * @brief Sets the number of displayed hangman parts
    * @param level Level od display (0-none, 5-all)
    */
    void setLevel(uint8_t level);

    /**
    * @brief Main module loop updating events
    * @param dt Delta time value
    */
    void update(const float& dt);

    /**
    * @brief Loop for rendering
    * @param target Pointer to the renderer
    */
    void render(sf::RenderTarget* target = nullptr);
};


#endif //HANGMAN_HANGMAN_H
