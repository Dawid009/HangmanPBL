#include "GameState.h"
#include <fstream>
#include <locale>

GameState::GameState(StateData* state_data)
        : State(state_data)
{
    this->initView();
    this->initFonts();
    this->keyboard = new Keyboard(this->font,this->stateData->gfxSettings);
    this->letterFields = new LetterFields(this->font,this->stateData->gfxSettings,L"Tekstabcd");
    this->hangman = new Hangman(this->stateData->gfxSettings);
}

GameState::~GameState()
{

}

void GameState::initFonts()
{
    if (!this->font.loadFromFile("Fonts/Caveat.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
    }
    std::locale::global(std::locale("pl_PL.UTF-8"));
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


void GameState::checkKeyboard(const uint8_t letter) {
    if(this->keyboard->IsPressed(letter)){

       if(auto points = this->letterFields->revealLetter(letter)){
            this->keyboard->SetButtonColor(letter,sf::Color(0,153,0));
           this->keyboard->SetButtonEnabled(letter,false);
       }else{
           this->keyboard->SetButtonColor(letter,sf::Color(250,0,0));
            this->keyboard->SetButtonEnabled(letter,false);
            misses++;
            this->hangman->setLevel(misses);
        };
    }
}

void GameState::update(const float& dt)
{
    this->updateMousePositions(&this->view);

    if (!this->paused) //gra w  trakcie
    {
        this->keyboard->update(mousePosWindow,dt);
        this->letterFields->update(dt);
        this->hangman->update(dt);

        //Sprawdzanie czy nacisniety przycisk
        for(uint8_t i=0;i<34;i++){
            checkKeyboard(i);
        }
    }
    else //gra zapauzowana
    {

    }
}

void GameState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;
    target->clear();
    target->draw(this->background);

    this->hangman->render(target);
    this->keyboard->render(target);
    this->letterFields->render(target);
}

