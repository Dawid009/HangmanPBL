#ifndef HANGMAN_STATE_H
#define HANGMAN_STATE_H

#include <SFML/Graphics.hpp>
#include <stack>
class State;

class StateData
{
public:
    StateData() {};

    //Variables
    sf::RenderWindow* window;
    std::stack<State*>* states;
};

class State {
protected:
    StateData* stateData;
    std::stack<State*>* states;
    sf::RenderWindow* window;

    bool quit;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;

public:
    State(StateData* state_data);
    virtual ~State();

    //Functions
    void endState();

    virtual void updateMousePositions(sf::View* view = nullptr);
    const bool& getQuit() const;
    virtual void update(const float& dt) = 0;
    virtual void render(sf::RenderTarget* target = nullptr) = 0;
};


#endif //HANGMAN_STATE_H
