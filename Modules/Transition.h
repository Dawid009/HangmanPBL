
#ifndef HANGMAN_TRANSITION_H
#define HANGMAN_TRANSITION_H
#include "SFML/Graphics.hpp"
#include "../States/State.h"

class Transition {

public:
    Transition();
    ~Transition();

    float alpha=0;


    void TransitTo()

    sf::RectangleShape* transitionScreen;

    void update(const float& dt);
    void render(sf::RenderTarget* target = NULL)
};


#endif //HANGMAN_TRANSITION_H
