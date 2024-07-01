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
#include "../Modules/Points.h"
#include "../Modules/SaveGame.h"
#include "../Modules/EndScreen.h"

/**
 * @class GameState
 * @brief Class reponsible for view and logic.
 */
class GameState : public State {
private:
    sf::View view; ///<Game view
    sf::Texture backgroundTexture;///<Background texture reference.
    PauseMenu* pmenu;///<in-game menu component pointer
    EndScreen* endScreen;///<End screen pointer
    sf::Clock endClock;///<End screen delay
    double totalTime=0;///<Total playtime in session
    sf::Clock timeClock;///<Time clock object
    bool initRevealed = false;///<Are letters from savegame revealed
    bool ended = false;///<Is game ended?
    int passwordLine;///<Id of the password
    SaveGame* saveGamePtr; ///<Savegame pointer
    Keyboard* keyboard; ///<Keyboard component pointer.
    LetterFields* letterFields; ///<Letter fields display component pointer.
    Hangman* hangman; ///<Hangman display component pointer.
    Points* pointsModule; ///<Pointer to points module
    sf::Text* fpsText; ///<Fps text
    sf::Text* pointsText; ///<Points text on the screen
    float delay=0;///<Fps update delay counter
    int misses=0;///<Number of misses
    int passes=0;///<Number of hits

    /**
    * @brief Function initializing gui.
    */
    void initView();

    /**
    * @brief Function picking random password from list
    * @param maxRow Number of file rows
    */
    void pickRandomPassword(std::wstring& stringRef,int maxRow);

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
    GameState(StateData* state_data, SaveGame * saveGame);

    /**
    * @brief Class destructor
    */
    ~GameState() override;

    /**
    * @brief Main state loop updating events
    * @param dt Delta time value
    */
    void update(const float& dt) final;

    /**
    * @brief Loop for rendering
    * @param target Pointer to the renderer
    */
    void render(sf::RenderTarget* target = NULL);


    /**
    * @brief Function updating PauseMenu component events
    */
    void updatePauseMenuButtons();

    /**
   * @brief Function updating End Screen component events
   */
    void updateEndScreenButtons();
};


#endif