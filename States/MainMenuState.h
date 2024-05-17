#ifndef HANGMAN_MAINMENUSTATE_H
#define HANGMAN_MAINMENUSTATE_H


#include "State.h"

class MainMenuState : public State{

private:
    sf::Texture backgroundTexture;
    sf::Texture titleTexture;
    sf::RectangleShape background;
    sf::RectangleShape title;
    sf::Font font;


    void initFonts();
    void initGui();
    void resetGui();

public:
    MainMenuState(StateData* state_data);
    virtual ~MainMenuState();

    void update(const float& dt) override;
    void render(sf::RenderTarget* target = nullptr) override;
};

#endif //HANGMAN_MAINMENUSTATE_H
