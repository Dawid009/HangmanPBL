#include "MainMenuState.h"
#include <iostream>
#include <locale>

#define NEW_GAME 1
#define CONTINUE 2
#define OPTIONS 3
#define QUIT 4

MainMenuState::MainMenuState(StateData* state_data)
        : State(state_data)
{
    this->initFonts();
    this->initGui();
    this->resetGui();
}

MainMenuState::~MainMenuState()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}


void MainMenuState::initFonts()
{
    if (!this->font.loadFromFile("Fonts/Caveat.ttf"))
    {
        throw("ERROR: Nie udalo sie zaladowac czcionki");
    }
}


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

    this->title.setPosition(sf::Vector2f(static_cast<float>(vm.width*0.13),static_cast<float>(vm.height*0.12)));
    this->title.setString("Hangman");
    this->title.setFont(this->font);
    this->title.setCharacterSize(gui::calcCharSize(vm,20));
    this->title.setFillColor(sf::Color(50,50,50,255));

    this->background.setTexture(&this->backgroundTexture);

    auto* ButtonInitParams = new gui::ButtonParams;

    //New game
    ButtonInitParams->x =  gui::calcX(14,vm);
    ButtonInitParams->y =  gui::calcY(35,vm);
    ButtonInitParams->width = static_cast<float>(gui::calcCharSize(vm,50)*7);
    ButtonInitParams->height = static_cast<float>(gui::calcCharSize(vm,50)*1.2);
    ButtonInitParams->font = &this->font;
    ButtonInitParams->text = L"New game";
    ButtonInitParams->character_size = gui::calcCharSize(vm,50);
    ButtonInitParams->hoverScale = 1.2f;
    ButtonInitParams->activeScale = 1.1f;
    this->buttons[NEW_GAME] = new gui::Button(ButtonInitParams);

    /*Continue*/


    //Options
    ButtonInitParams->y =  gui::calcY(43,vm);
    ButtonInitParams->text = L"Options";
    this->buttons[OPTIONS] = new gui::Button(ButtonInitParams);


    //Exit
    ButtonInitParams->y =  gui::calcY(70,vm);
    ButtonInitParams->text = L"Quit";

    ButtonInitParams->text_idle_color= sf::Color(40, 40, 40, 255);
    ButtonInitParams->text_hover_color= sf::Color(25, 25, 25, 255),
    ButtonInitParams->text_active_color= sf::Color(10, 10, 10, 255),
    this->buttons[QUIT] = new gui::Button(ButtonInitParams);
    delete ButtonInitParams;
}

void MainMenuState::resetGui()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
    this->buttons.clear();
    this->initGui();
}

void MainMenuState::updateButtons(const float& dt)
{
    for (auto &it : this->buttons)
    {
        it.second->update(this->mousePosWindow,dt);
    }

    //Nowa gra

    if (this->buttons[NEW_GAME]->isPressed())
    {
        this->states->push(new GameState(this->stateData));
    }

    if (this->buttons[QUIT]->isPressed())
    {
        this->endState();
    }
}

void MainMenuState::update(const float& dt)
{
    this->updateMousePositions();
    this->updateButtons(dt);
}


void MainMenuState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    target->draw(this->background);
    target->draw(this->title);


    //Renderowanie buttonów
    for (auto &it : this->buttons)
    {
        it.second->render(*target);
    }
}



