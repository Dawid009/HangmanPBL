#include "Game.h"


Game::Game()
{
    this->initVariables();
    this->initWindow();
}

Game::~Game()
{
    //Zwalnianie pamięci
    delete this->window;
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
    //TODO: Stałe wartości przerobić na zmienne
    this->window = new sf::RenderWindow(sf::VideoMode(800,600), "Hangman",sf::Style::Close);
    this->window->setFramerateLimit(60);
    this->window->setVerticalSyncEnabled(false);
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


/*****************************************************************************
** Function name:      update
** Description:        Główna pętla gry
*****************************************************************************/
void Game::update()
{
    this->updateEvents();
}


/*****************************************************************************
** Function name:      render
** Description:        Odpowiada za renderowanie obrazu
*****************************************************************************/
void Game::render()
{
    this->window->clear();
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