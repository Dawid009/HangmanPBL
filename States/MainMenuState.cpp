#include "MainMenuState.h"
#include <locale>
#include "SettingsState.h"
#include "SavesListState.h"

#define NEW_GAME 1
#define CONTINUE 2
#define OPTIONS 3
#define QUIT 4
#define SAVES 5

MainMenuState::MainMenuState(StateData* state_data)
        : State(state_data), stateptr(nullptr)
{
    this->initFonts();
    this->initGui();
    this->resetGui();
}

MainMenuState::~MainMenuState()
{
    for (auto &it : this->buttons)
    {
        delete it.second;
    }
}


void MainMenuState::initFonts()
{
    if (!this->font.loadFromFile(this->stateData->localpath+"Fonts/Caveat.ttf"))
    {
        throw("ERROR: Nie udalo sie zaladowac czcionki");
    }
}


void MainMenuState::initGui()
{
    const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

    this->background.setSize(sf::Vector2f(static_cast<float>(vm.width),static_cast<float>(vm.height)));

    if (!this->backgroundTexture.loadFromFile(this->stateData->localpath+"Images/background.jpg"))
    {
        throw "ERROR::MAIN_MENU::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
    }

    this->fade.setSize(
           sf::Vector2f
                    (
                            static_cast<float>(vm.width),
                            static_cast<float>(vm.height)
                    )
    );

    this->fade.setFillColor(sf::Color(50,50,50,255));


    this->title.setPosition(sf::Vector2f(static_cast<float>(vm.width*0.13),static_cast<float>(vm.height*0.12)));
    this->title.setString("Wisielec");
    this->title.setFont(this->font);
    this->title.setStyle(1);
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
    ButtonInitParams->text = L"Graj";
    ButtonInitParams->character_size = gui::calcCharSize(vm,50);
    ButtonInitParams->hoverScale = 1.2f;
    ButtonInitParams->activeScale = 1.1f;
    ButtonInitParams->text_idle_color= sf::Color(40, 40, 40, 255);
    ButtonInitParams->text_hover_color= sf::Color(25, 25, 25, 255),
    ButtonInitParams->text_active_color= sf::Color(10, 10, 10, 255),
    this->buttons[SAVES] = new gui::Button(ButtonInitParams);

    //Options
    ButtonInitParams->y =  gui::calcY(43,vm);
    ButtonInitParams->text = L"Opcje";
    this->buttons[OPTIONS] = new gui::Button(ButtonInitParams);

    //Exit
    ButtonInitParams->y =  gui::calcY(70,vm);
    ButtonInitParams->text = L"Wyjście";


    this->buttons[QUIT] = new gui::Button(ButtonInitParams);
    delete ButtonInitParams;
}


void MainMenuState::resetGui()
{
    for (auto &it : this->buttons)
    {
        delete it.second;
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

    if (this->buttons[SAVES]->isPressed())
    {
        stateptr = new SavesListState(this->stateData);
    }

    if (this->buttons[OPTIONS]->isPressed())
    {
        stateptr = new SettingsState(this->stateData);
    }

    if (this->buttons[QUIT]->isPressed())
    {
        this->endState();
        window->close();
    }
}


void MainMenuState::update(const float& dt)
{
    if(fadein){
        this->fade.setFillColor(sf::Color(20,20,20,this->fade.getFillColor().a-dt*1000));
        if(this->fade.getFillColor().a<20){
            fadein=false;
        }
        time.restart();
    }

    if (!pushedNew && stateptr!= nullptr) {
        this->fade.setFillColor(sf::Color(20,20,20,this->fade.getFillColor().a+dt*1000));
        if(this->fade.getFillColor().a>240){
            pushedNew=true;
            this->states->pop();
            this->stateData->states->push(stateptr);
        }
    }

    this->updateMousePositions();
    if(this->stateData->gfxSettings->resolution.width != background.getSize().x || this->stateData->gfxSettings->resolution.height != background.getSize().y){
        resetGui();
    }
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
    target->draw(this->fade);
}



