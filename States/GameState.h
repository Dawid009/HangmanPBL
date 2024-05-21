#ifndef HANGMAN_GAMESTATE_H
#define HANGMAN_GAMESTATE_H
#include <SFML/Graphics.hpp>
#include "State.h"
#include "../Modules/Keyboard.h"
#include "../Modules/LetterFields.h"

class GameState : public State {
private:
    //Zmienne
    sf::View view;
    sf::Texture backgroundTexture;
    sf::Font font;

    Keyboard* keyboard;
    LetterFields* letterFields;

    //Funkcje
    void initView();
    void initFonts();
    void checkKeyboard(char letter);

public:
    //Konstruktor/Destruktor
    GameState(StateData* state_data);
    virtual ~GameState();


    //Funkcje
    void update(const float& dt);
    void render(sf::RenderTarget* target = NULL);
};


#endif //HANGMAN_GAMESTATE_H
