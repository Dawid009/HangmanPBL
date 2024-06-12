#include "LoadingState.h"
#include "MainMenuState.h"

void LoadingState::initFonts()
{
    if (!this->font.loadFromFile(this->stateData->localpath+"Fonts/Caveat.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
    }
}

void LoadingState::initGui()
{
    const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

    this->background.setSize(
            sf::Vector2f
                    (
                            static_cast<float>(vm.width),
                            static_cast<float>(vm.height)
                    )
    );

    this->fade.setSize(
            sf::Vector2f
                    (
                            static_cast<float>(vm.width),
                            static_cast<float>(vm.height)
                    )
    );
    this->fade.setFillColor(sf::Color(0,0,0,255));

    if (!this->backgroundTexture.loadFromFile(this->stateData->localpath+"Images/LS.png"))
    {
        throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
    }

    this->background.setTexture(&this->backgroundTexture);

    title.setFillColor(sf::Color::Black);
    title.setCharacterSize(gui::calcCharSize(vm,20));
    title.setPosition(sf::Vector2f(gui::calcX(30,vm),gui::calcY(40,vm)));
    title.setString("WISIELEC");
    title.setFont(this->font);
    title.setStyle(1);
}


LoadingState::LoadingState(StateData* state_data)
        : State(state_data)
{
    this->initFonts();
    this->initGui();
}

LoadingState::~LoadingState()
{


}


void LoadingState::update(const float& dt)
{
    if(fadein){
        this->fade.setFillColor(sf::Color(20,20,20,this->fade.getFillColor().a-dt*150));
        if(this->fade.getFillColor().a<20){
            fadein=false;
        }
        time.restart();
    }
    if (time.getElapsedTime().asSeconds() >= 1.5f&& !fadein) {
        this->fade.setFillColor(sf::Color(20,20,20,this->fade.getFillColor().a+dt*800));
        if(this->fade.getFillColor().a>240){

            MainMenuState* temp = new MainMenuState(stateData);
            delete this->states->top();
            this->states->pop();
            this->stateData->states->push(temp);
        }
    }
}


void LoadingState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    target->draw(this->background);
    target->draw(title);
    target->draw(fade);
}