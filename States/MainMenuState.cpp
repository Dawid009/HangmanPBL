#include "MainMenuState.h"
#include <iostream>


MainMenuState::MainMenuState(StateData* state_data)
        : State(state_data)
{
    //this->initFonts();
    this->initGui();
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
    const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

    this->background.setSize(sf::Vector2f(static_cast<float>(vm.width),static_cast<float>(vm.height)));

    if (!this->backgroundTexture.loadFromFile("Resources/background.jpg"))
    {
        throw "ERROR::MAIN_MENU::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
    }

    if (!this->titleTexture.loadFromFile("Resources/title.png"))
    {
        throw "ERROR::MAIN_MENU::FAILED_TO_LOAD_TITLE_TEXTURE";
    }

    this->title.setSize(sf::Vector2f(static_cast<float>(vm.width*0.30),static_cast<float>(vm.height*0.12)));
    this->title.setPosition(sf::Vector2f(static_cast<float>(vm.width*0.10),static_cast<float>(vm.height*0.12)));
    this->title.setTexture(&this->titleTexture);
    this->background.setTexture(&this->backgroundTexture);




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
    target->draw(this->title);

}



