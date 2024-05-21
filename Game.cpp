#include "Game.h"


Game::Game()
{
    this->initVariables();
    this->initGraphicsSettings();
    this->initWindow();
    this->initStateData();
    this->initStates();
}

Game::~Game()
{
    //Zwalnianie pamięci
    delete this->window;

    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}


/*****************************************************************************
** Function name:      initVariables
** Description:        Inicjalizuje podstawowowe parametry klasy "Game"
*****************************************************************************/
void Game::initVariables()
{
    this->window = nullptr;
    this->dt = 0.f;
}


/*****************************************************************************
** Function name:      initWindow
** Description:        Tworzy okno o określonych parametrach
*****************************************************************************/
void Game::initWindow()
{

    if(this->gfxSettings.fullscreen)
        this->window = new sf::RenderWindow(
                this->gfxSettings.resolution,
                this->gfxSettings.title,
                sf::Style::Fullscreen,
                this->gfxSettings.contextSettings);
    else
        this->window = new sf::RenderWindow(
                this->gfxSettings.resolution,
                this->gfxSettings.title,
                sf::Style::Titlebar | sf::Style::Close,
                this->gfxSettings.contextSettings);



    this->window->setFramerateLimit(this->gfxSettings.frameRateLimit);
    this->window->setVerticalSyncEnabled(this->gfxSettings.verticalSync);
}


/*****************************************************************************
** Function name:      updateDt
** Description:        Oblicza DeltaTime
*****************************************************************************/
void Game::updateDt()
{
    //Aktualizuje zmienną DeltaTime
    this->dt = this->dtClock.restart().asSeconds();
}


/*****************************************************************************
** Function name:      updateEvents
** Description:        Aktualizuje eventy SFML
*****************************************************************************/
void Game::updateEvents()
{
    while (this->window->pollEvent(this->sfEvent))
    {
        if (this->sfEvent.type == sf::Event::Closed)
            this->window->close();
    }
}


void Game::initGraphicsSettings()
{

    this->gfxSettings.loadFromFile("Config/graphics.ini");
}

/*****************************************************************************
** Function name:      initStateData
** Description:        Inicializuje kontener danych na temat state
*****************************************************************************/
void Game::initStateData()
{
    this->stateData.gfxSettings = &this->gfxSettings;
    this->stateData.window = this->window;
    this->stateData.states = &this->states;
}


/*****************************************************************************
** Function name:      initStates
** Description:        Tworzy pierwszy element - menu główne
*****************************************************************************/
void Game::initStates()
{
    this->states.push(new MainMenuState(&this->stateData));
}


/*****************************************************************************
** Function name:      update
** Description:        Główna pętla gry
*****************************************************************************/
void Game::update()
{
    this->updateEvents();


    if (!this->states.empty())
    {
        if (this->window->hasFocus())
        {
            this->states.top()->update(this->dt);

            if (this->states.top()->getQuit())
            {
                this->states.top()->endState();
                delete this->states.top();
                this->states.pop();
            }
        }
    }
    //Application end
    else
    {
        this->window->close();
    }
}


/*****************************************************************************
** Function name:      render
** Description:        Odpowiada za renderowanie obrazu
*****************************************************************************/
void Game::render()
{
    this->window->clear();

    if (!this->states.empty())
        this->states.top()->render();

    this->window->display();
}


/*****************************************************************************
** Function name:      run
** Description:        Start gry, główna pętla zadań.
*****************************************************************************/
void Game::run()
{
    //Główna pętla gry
    while (this->window->isOpen())
    {
        this->updateDt();
        this->update();
        this->render();
    }
}