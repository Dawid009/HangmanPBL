/**
 * @file Game.h
 * @brief Base Game file
 */
#ifndef HANGMAN_GAME_H
#define HANGMAN_GAME_H

#include <SFML/Graphics.hpp>
#include "States/MainMenuState.h"

/** @class Game
 * @brief The basic class of the game
 * */
class Game {

private:
    sf::RenderWindow *window;///<Main application window pointer
    sf::Event sfEvent;///<SFML Event object
    sf::Clock dtClock;///<SFML Clock object
    StateData stateData;///<Data needed for valid function calls
    std::stack<State*> states;///<Stack storing views pointers
    GraphicsSettings gfxSettings;///<Graphics setting class object
    float dt; ///<Delta time value

    /**
    * @brief A function that reads graphic settings from a file
    */
    void initGraphicsSettings();

    /**
    * @brief Function to assign basic values to variables
    */
    void initVariables();

    /**
    * @brief A function that creates a game window
    */
    void initWindow();

    /**
    * @brief Function that creates and completes the state data object
    */
    void initStateData();

    /**
    * @brief Creates the first view to be displayed
    */
    void initStates();

public:
    /**
    * @brief Class constructor
    */
    Game();

    /**
    * @brief Class destructor
    */
    virtual ~Game();

    /**
    * @brief Basic game loop handling events
    */
    void update();

    /**
    * @brief Function responsible for updating the DT variable
    */
    void updateDt();

    /**
    * @brief Function responsible for rendering the first item on the view stack
    */
    void render();

    /**
    * @brief A feature that runs the entire game
    */
    void run();
};


#endif //HANGMAN_GAME_H
