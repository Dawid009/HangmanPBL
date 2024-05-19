#include "GameState.h"


void GameState::initFonts()
{
    if (!this->font.loadFromFile("Fonts/Lucida.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
    }
}


void GameState::initView()
{
    const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
    this->background.setSize(sf::Vector2f(static_cast<float>(vm.width),static_cast<float>(vm.height)));

    if (!this->backgroundTexture.loadFromFile("Resources/gamebackground.jpg"))
    {
        throw "ERROR::MAIN_MENU::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
    }

    this->background.setTexture(&this->backgroundTexture);
}


GameState::GameState(StateData* state_data)
        : State(state_data)
{
    this->initView();
    this->initFonts();
}

GameState::~GameState()
{

}

void GameState::update(const float& dt)
{
    this->updateMousePositions(&this->view);

    if (!this->paused) //gra w  trakcie
    {
        //gra
    }
    else //gra zapauzowana
    {
        //menu
    }
}

void GameState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    target->draw(this->background);
}