#ifndef HANGMAN_GAMESTATE_H
#define HANGMAN_GAMESTATE_H
#include <SFML/Graphics.hpp>
#include "State.h"

class GameState : public State {
private:
    //Zmienne
    sf::View view;
    sf::Texture backgroundTexture;
    sf::Font font;

    //Funkcje
    void initView();
    void initFonts();

public:
    //Konstruktor/Destruktor
    GameState(StateData* state_data);
    virtual ~GameState();


    //Funkcje
    void update(const float& dt);
    void render(sf::RenderTarget* target = NULL);


};


#endif //HANGMAN_GAMESTATE_H
