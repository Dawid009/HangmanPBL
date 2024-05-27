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

/**
 * @class GameState
 * @brief Class reponsible for view and logic.
 */
class GameState : public State {
private:

    sf::View view; ///<
    sf::Texture backgroundTexture;///<Background texture reference.
    sf::Font font;///<Font reference requiered to render text.

    Keyboard* keyboard; ///<Keyboard component pointer.
    LetterFields* letterFields; ///<Letter fields display component pointer.
    Hangman* hangman; ///<Hangman display component pointer.

    int misses=0;

    void initView();
    void initFonts();
    void checkKeyboard(uint8_t letter);

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
};


#endif //HANGMAN_GAMESTATE_H
