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

    auto* ButtonInitParams = new gui::ButtonParams;

    //Nowa gra
    ButtonInitParams->x =  gui::calcX(14,vm);
    ButtonInitParams->y =  gui::calcY(35,vm);
    ButtonInitParams->width = static_cast<float>(gui::calcCharSize(vm,50)*7);
    ButtonInitParams->height = static_cast<float>(gui::calcCharSize(vm,50)*1.2);
    ButtonInitParams->font = &this->font;
    ButtonInitParams->text = "Nowa gra";
    ButtonInitParams->character_size = gui::calcCharSize(vm,50);
    ButtonInitParams->hoverScale = 1.2f;
    ButtonInitParams->activeScale = 1.1f;
    //Linie pomocnicze do debugowania
    ButtonInitParams->drawDebugBorder = true;
    this->buttons["GAME_STATE"] = new gui::Button(ButtonInitParams);

    ButtonInitParams->initEnable = false;

    //Kontynuuj
    ButtonInitParams->y =  gui::calcY(42,vm);
    ButtonInitParams->text = "Kontynuuj";
    this->buttons["CONTINUE_STATE"] = new gui::Button(ButtonInitParams);

    ButtonInitParams->initEnable = true;
    //Opcje
    ButtonInitParams->y =  gui::calcY(55,vm);
    ButtonInitParams->text = "Opcje";
    this->buttons["OPTIONS_STATE"] = new gui::Button(ButtonInitParams);


    //Wyjscie
    ButtonInitParams->y =  gui::calcY(70,vm);
    ButtonInitParams->text = "Wyjscie";
    ButtonInitParams->text_idle_color= sf::Color(40, 40, 40, 255);
    ButtonInitParams->text_hover_color= sf::Color(25, 25, 25, 255),
    ButtonInitParams->text_active_color= sf::Color(10, 10, 10, 255),
    this->buttons["EXIT_STATE"] = new gui::Button(ButtonInitParams);
    delete ButtonInitParams;
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



