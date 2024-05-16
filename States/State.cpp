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

/*****************************************************************************
** Function name:      getQuit
** Description:        Zakonczenie programu
*****************************************************************************/
const bool & State::getQuit() const
{
    return this->quit;
}

/*****************************************************************************
** Function name:      updateMousePositions
** Description:        Aktualizuje pozycje myszki na ekranie i oknie
*****************************************************************************/
void State::updateMousePositions(sf::View* view)
{
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
}

/*****************************************************************************
** Function name:      endState
** Description:        Zakonczenie działania state
*****************************************************************************/
void State::endState()
{
    this->quit = true;
}


