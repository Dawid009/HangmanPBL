#include "MainMenuState.h"
#include <iostream>


MainMenuState::MainMenuState(StateData* state_data)
        : State(state_data)
{
    //this->initFonts();
    //this->initGui();
    //this->resetGui();
}
MainMenuState::~MainMenuState()
{

}


/*****************************************************************************
** Function name:      initFonts
** Description:        Odczytuje czcionke z pliku
*****************************************************************************/
void MainMenuState::initFonts()
{
    if (!this->font.loadFromFile("Fonts/Arial.ttf"))
    {
        throw("ERROR: Nie udalo sie zaladowac czcionki");
    }
}


/*****************************************************************************
** Function name:      initGui
** Description:        Inicializuje GUI
*****************************************************************************/
void MainMenuState::initGui()
{
    //tu powstanie tworzenie podstawowego widoku
}


/*****************************************************************************
** Function name:      update
** Description:        Główna pętla dla tego state
*****************************************************************************/
void MainMenuState::update(const float& dt)
{
    this->updateMousePositions();
}



/*****************************************************************************
** Function name:      render
** Description:        Główna pętla renderująca dla tego state
*****************************************************************************/
void MainMenuState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    target->draw(this->background);

}



