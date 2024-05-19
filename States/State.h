#ifndef HANGMAN_STATE_H
#define HANGMAN_STATE_H

#include <SFML/Graphics.hpp>
#include <stack>
#include "../Modules/GraphicsSettings.h"

class State;

class StateData
{
public:
    StateData() {};

    //Zmienne
    sf::RenderWindow* window;
    GraphicsSettings* gfxSettings;
    std::stack<State*>* states;
};

class State {
protected:
    //Zmienne
    StateData* stateData;
    std::stack<State*>* states;
    sf::RenderWindow* window;
    sf::Texture backgroundTexture;
    sf::RectangleShape background;

    bool quit;
    bool paused;

    //Przechowuja info o pozycji myszki na ekranie/oknie
    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;

public:
    //Konstruktor/Destruktor
    State(StateData* state_data);
    virtual ~State();

    //Funkcje
    void endState();
    virtual void updateMousePositions(sf::View* view = nullptr);
    const bool& getQuit() const;
    virtual void update(const float& dt) = 0;
    virtual void render(sf::RenderTarget* target = nullptr) = 0;
};


#endif //HANGMAN_STATE_H
