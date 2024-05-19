#ifndef HANGMAN_MAINMENUSTATE_H
#define HANGMAN_MAINMENUSTATE_H

#include "State.h"
#include "../Gui.h"

class MainMenuState : public State{

private:
    //Zmienne
    sf::Texture backgroundTexture;
    sf::Texture titleTexture;
    sf::RectangleShape background;
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
    void updateButtons();
    void update(const float& dt) override;
    void renderButtons(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr) override;
};

#endif //HANGMAN_MAINMENUSTATE_H
