/**
 * @file GameState.h
 * @brief Game state view class
 */
#ifndef HANGMAN_GAMESTATE_H
#define HANGMAN_GAMESTATE_H
#include <SFML/Graphics.hpp>
#include "State.h"
#include "../Modules/Keyboard.h"
#include "../Modules/LetterFields.h"
#include "../Modules/Hangman.h"
#include "../Modules/PauseMenu.h"

/**
 * @class GameState
 * @brief Class reponsible for view and logic.
 */
class GameState : public State {
private:
    sf::View view; ///<Game view
    sf::Texture backgroundTexture;///<Background texture reference.
    sf::Font font;///<Font reference requiered to render text.
    sf::RenderTexture renderTexture;///<deferred renderer screen view
    sf::Sprite renderSprite; ///<deferred renderer sprite
    PauseMenu* pmenu;///<in-game menu component pointer

    Keyboard* keyboard; ///<Keyboard component pointer.
    LetterFields* letterFields; ///<Letter fields display component pointer.
    Hangman* hangman; ///<Hangman display component pointer.
    sf::Text* fpsText; ///<Fps text
    float delay=0;///<Fps update delay counter
    int misses=0;///<Misses count

    /**
    * @brief Creates a renderer
    */
    void initDeferredRender();

    /**
    * @brief Function initializing gui.
    */
    void initView();

    /**
    * @brief Function initializing fonts required to display text.
    */
    void initFonts();

    /**
    * @brief Function checking if button is pressed
    * @param letter Button id
    */
    void checkKeyboard(uint8_t letter);

    /**
    * @brief Function initializing PauseMenu component
    */
    void initPauseMenu();

public:
    /**
    * @brief Class constructor
    * @param state_date Pointer to main state data.
    */
    GameState(StateData* state_data);

    /**
    * @brief Class destructor
    */
    virtual ~GameState();

    /**
    * @brief Main state loop updating events
    * @param dt Delta time value
    */
    void update(const float& dt);

    /**
    * @brief Loop for rendering
    * @param target Pointer to the renderer
    */
    void render(sf::RenderTarget* target = NULL);


    /**
    * @brief Function updating PauseMenu component events
    */
    void updatePauseMenuButtons();
};


#endif //HANGMAN_GAMESTATE_H
