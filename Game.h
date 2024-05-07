#ifndef HANGMAN_GAME_H
#define HANGMAN_GAME_H

#include <SFML/Graphics.hpp>


class Game {

private:
    sf::RenderWindow *window;
    sf::Event sfEvent;
    sf::Clock dtClock;
    //DeltaTime
    float dt;


    //Funkcje prywatne
    void initVariables();
    void initWindow();

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
