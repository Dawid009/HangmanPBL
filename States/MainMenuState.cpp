#include "MainMenuState.h"
#include <iostream>

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


/*****************************************************************************
** Function name:      initFonts
** Description:        Odczytuje czcionke z pliku
*****************************************************************************/
void MainMenuState::initFonts()
{
    if (!this->font.loadFromFile("Fonts/Lucida.ttf"))
    {
        throw("ERROR: Nie udalo sie zaladowac czcionki");
    }
}


/*****************************************************************************
** Function name:      initGui
** Description:        Tworzy przyciski, background i inne teksty
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

    const int colorIdle = 70;
    const int colorHover = 40;
    const int colorActive = 20;

    this->buttons["GAME_STATE"] = new gui::Button(
            gui::calcX(14,vm),gui::calcY(35,vm),
            static_cast<float>(gui::calcCharSize(vm,50)*7),
            static_cast<float>(gui::calcCharSize(vm,50)*1.2),
            &this->font,"Nowa gra",gui::calcCharSize(vm,50),3.f,
            sf::Color(colorIdle, colorIdle, colorIdle, 255),
            sf::Color(colorHover, colorHover, colorHover, 255),
            sf::Color(colorActive, colorActive, colorActive, 255),
            sf::Color::Transparent,
            sf::Color::Transparent,
            sf::Color::Transparent,
            1,1.2f,1.1f
    );
    this->buttons["CONTINUE_STATE"] = new gui::Button(
            gui::calcX(14,vm),gui::calcY(42,vm),
            static_cast<float>(gui::calcCharSize(vm,50)*7),
            static_cast<float>(gui::calcCharSize(vm,50)*1.2),
            &this->font,"Kontynuuj",gui::calcCharSize(vm,50),3.f,
            sf::Color(colorIdle, colorIdle, colorIdle, 100),
            sf::Color(colorHover, colorHover, colorHover, 255),
            sf::Color(colorActive, colorActive, colorActive, 255),
            sf::Color::Transparent,
            sf::Color::Transparent,
            sf::Color::Transparent,
            1,1.2f,1.1f
    );

    this->buttons["OPTIONS_STATE"] = new gui::Button(
            gui::calcX(14,vm),gui::calcY(55,vm),
            static_cast<float>(gui::calcCharSize(vm,50)*7),
            static_cast<float>(gui::calcCharSize(vm,50)*1.2),
            &this->font,"Opcje",gui::calcCharSize(vm,50),3.f,
            sf::Color(colorIdle, colorIdle, colorIdle, 255),
            sf::Color(colorHover, colorHover, colorHover, 255),
            sf::Color(colorActive, colorActive, colorActive, 255),
            sf::Color::Transparent,
            sf::Color::Transparent,
            sf::Color::Transparent,
            1,1.2f,1.1f
    );

    this->buttons["EXIT_STATE"] = new gui::Button(
            gui::calcX(14,vm),gui::calcY(75,vm),
            static_cast<float>(gui::calcCharSize(vm,50)*7),
            static_cast<float>(gui::calcCharSize(vm,50)*1.2),
            &this->font,"Wyjscie",gui::calcCharSize(vm,50),3.f,
            sf::Color(40, 40, 40, 255),
            sf::Color(25, 25, 25, 255),
            sf::Color(10, 10, 10, 255),
            sf::Color::Transparent,
            sf::Color::Transparent,
            sf::Color::Transparent,
            1,1.2f,1.1f
            );
}

/*****************************************************************************
** Function name:      resetGui
** Description:        wyświetla całe Gui na nowo
*****************************************************************************/
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

/*****************************************************************************
** Function name:      updateButtons
** Description:        odpowiada za działanie buttonow
*****************************************************************************/
void MainMenuState::updateButtons(const float& dt)
{
    for (auto &it : this->buttons)
    {
        it.second->update(this->mousePosWindow,dt);
    }

    //Nowa gra
    if (this->buttons["GAME_STATE"]->isPressed())
    {
        std::cout<<"Dziala!"<<std::endl;
        this->states->push(new GameState(this->stateData));
    }

    /*
     * Dodać obsluge reszty przyciskow
     */

    //wyjscie
    if (this->buttons["EXIT_STATE"]->isPressed())
    {
        this->endState();
    }
}


/*****************************************************************************
** Function name:      update
** Description:        Główna pętla dla tego state
*****************************************************************************/
void MainMenuState::update(const float& dt)
{
    this->updateMousePositions();
    this->updateButtons(dt);
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


    //Renderowanie buttonów
    for (auto &it : this->buttons)
    {
        it.second->render(*target);
    }
}



