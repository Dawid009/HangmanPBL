#ifndef HANGMAN_MAINMENUSTATE_H
#define HANGMAN_MAINMENUSTATE_H

#include "State.h"
#include "../Modules/Gui.h"
#include "GameState.h"

class MainMenuState : public State{

private:
    //Zmienne
    sf::Texture titleTexture;
    sf::RectangleShape title;
    sf::Font font;
    std::map<std::string, gui::Button*> buttons;

    //Funkcje
    void initFonts();
    void initGui();
    void resetGui();

public:
    //Konstruktor/Destruktor
    MainMenuState(StateData* state_data);
    virtual ~MainMenuState();

    //Funkcje
    void updateButtons(const float& dt);
    void update(const float& dt) override;
    void render(sf::RenderTarget* target = nullptr) override;
};

#endif //HANGMAN_MAINMENUSTATE_H
