#include "State.h"

State::State(StateData* state_data)
{
    this->stateData = state_data;
    this->window = state_data->window;
    this->states = state_data->states;
    this->quit = false;
}

State::~State()
{

}

const bool & State::getQuit() const
{
    return this->quit;
}

void State::updateMousePositions(sf::View* view)
{
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
}

void State::endState()
{
    this->quit = true;
}


