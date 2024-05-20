#include "GameState.h"



GameState::GameState(StateData* state_data)
        : State(state_data)
{
    this->initView();
    this->initFonts();
    this->keyboard = new Keyboard(this->font,this->stateData->gfxSettings);
}

GameState::~GameState()
{

}


/*****************************************************************************
** Function name:      initFonts
** Description:        Wczytuje czcionkę z pliku
*****************************************************************************/
void GameState::initFonts()
{
    if (!this->font.loadFromFile("Fonts/Lucida.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
    }
}

/*****************************************************************************
** Function name:      initView
** Description:        Tworzy widok gry
*****************************************************************************/
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


/*****************************************************************************
** Function name:      update
** Description:        Pętla odpowiadająca za zdarzenia
*****************************************************************************/
void GameState::update(const float& dt)
{
    this->updateMousePositions(&this->view);

    if (!this->paused) //gra w  trakcie
    {
        this->keyboard->update(mousePosWindow,dt);
    }
    else //gra zapauzowana
    {
        //menu
    }
}

/*****************************************************************************
** Function name:      update
** Description:        Pętla odpowiadająca za wyświetlanie
*****************************************************************************/
void GameState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;
    target->clear();

    target->draw(this->background);
    this->keyboard->render(target);



}