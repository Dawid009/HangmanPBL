#ifndef HANGMAN_GAME_H
#define HANGMAN_GAME_H

#include <SFML/Graphics.hpp>
#include "States/MainMenuState.h"

class Game {

private:
    sf::RenderWindow *window;
    sf::Event sfEvent;
    sf::Clock dtClock;
    StateData stateData;
    std::stack<State*> states;
    GraphicsSettings gfxSettings;

    //DeltaTime
    float dt;


    //Funkcje prywatne
    void initGraphicsSettings();
    void initVariables();
    void initWindow();
    void initStateData();
    void initStates();

public:
    //Konstruktor/Destruktor
    Game();
    virtual ~Game();

    //Funkcje update
    void update();
    void updateDt();
    void updateEvents();

    //Renderowanie
    void render();

    //Start
    void run();

};


#endif //HANGMAN_GAME_H
