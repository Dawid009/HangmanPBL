#include "GameState.h"
#include <fstream>
#include <locale>

GameState::GameState(StateData* state_data)
        : State(state_data)
{
    this->paused = false;
    this->initDeferredRender();
    this->initView();
    this->initFonts();
    this->initPauseMenu();
    this->keyboard = new Keyboard(this->font,this->stateData->gfxSettings);
    this->letterFields = new LetterFields(this->font,this->stateData->gfxSettings,L"Tekstabcd");
    this->hangman = new Hangman(this->stateData->gfxSettings);
}

GameState::~GameState()
{

}

void GameState::initDeferredRender()
{
    this->renderTexture.create(
            this->stateData->gfxSettings->resolution.width,
            this->stateData->gfxSettings->resolution.height
    );

    this->renderSprite.setTexture(this->renderTexture.getTexture());
    this->renderSprite.setTextureRect(
            sf::IntRect(
                    0,
                    0,
                    this->stateData->gfxSettings->resolution.width,
                    this->stateData->gfxSettings->resolution.height
            )
    );
}



void GameState::initFonts()
{
    if (!this->font.loadFromFile(this->stateData->localpath+"Fonts/Caveat.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
    }
    std::locale::global(std::locale("pl_PL.UTF-8"));
}


void GameState::initView()
{
    const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

    if(stateData->showfps){
        fpsText = new sf::Text();
        fpsText->setString("");
        fpsText->setFont(this->font);
        fpsText->setCharacterSize(gui::calcCharSize(vm,70.f));
        fpsText->setPosition(sf::Vector2f(gui::calcX(0.5f,vm),gui::calcY(0.5f,vm)));
        fpsText->setFillColor(sf::Color(20, 20, 20, 255));
    }

    this->background.setSize(sf::Vector2f(static_cast<float>(vm.width),static_cast<float>(vm.height)));

    if (!this->backgroundTexture.loadFromFile(this->stateData->localpath+"Images/gamebackground.jpg"))
    {
        throw "ERROR::MAIN_MENU::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
    }

    this->background.setTexture(&this->backgroundTexture);
}


void GameState::initPauseMenu()
{
    const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
    this->pmenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);
    this->pmenu->addButton("QUIT", gui::calcY(74.f, vm), gui::calcX(13.f, vm), gui::calcY(6.f, vm), gui::calcCharSize(vm), L"Quit");
    this->pmenu->addButton("OPTIONS", gui::calcY(44.f, vm), gui::calcX(13.f, vm), gui::calcY(6.f, vm), gui::calcCharSize(vm), L"Options");
    this->pmenu->addButton("CONTINUE", gui::calcY(35.f, vm), gui::calcX(13.f, vm), gui::calcY(6.f, vm), gui::calcCharSize(vm), L"Continue");
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


void GameState::updatePauseMenuButtons()
{
    if (this->pmenu->isButtonPressed("QUIT"))
        this->endState();
    if (this->pmenu->isButtonPressed("CONTINUE"))
        this->paused = false;
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
        for(uint8_t i{0};i<34;i++){
            checkKeyboard(i);
        }

        if(this->keyboard->IsPressed(L'*')){
            this->paused = true;
        }

    }
    else //gra zapauzowana
    {
        this->pmenu->update(this->mousePosWindow,dt);
        this->updatePauseMenuButtons();
    }


    if(this->stateData->showfps && delay>1.5f){
        fpsText->setString(std::to_string(static_cast<int>(1/dt)));
        delay=0;
    }else{
        delay+=dt;
    }
}


void GameState::render(sf::RenderTarget* target)
{

    this->renderTexture.clear();
    if (!target)
        target = this->window;
    this->renderTexture.clear();
    target->draw(this->background);
    renderTexture.draw(this->background);
    this->hangman->render(&renderTexture);
    this->keyboard->render(&renderTexture);
    this->letterFields->render(&renderTexture);

    if (this->paused)
    {
        this->pmenu->render(this->renderTexture);
    }

    this->renderTexture.display();
    this->renderSprite.setTexture(this->renderTexture.getTexture());
    target->draw(renderSprite);

    if(this->stateData->showfps){
        target->draw(*fpsText);
    }
}

