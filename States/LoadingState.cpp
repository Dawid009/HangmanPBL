#include "LoadingState.h"
#include "MainMenuState.h"

LoadingState::LoadingState(StateData* state_data)
        : State(state_data)
{
    this->initFonts();
    this->initGui();
}


LoadingState::~LoadingState() = default;

void LoadingState::initGui()
{
    const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

    this->background.setSize(sf::Vector2f(static_cast<float>(vm.width),static_cast<float>(vm.height)));
    this->fade.setSize(sf::Vector2f(static_cast<float>(vm.width),static_cast<float>(vm.height)));
    this->fade.setFillColor(sf::Color(0,0,0,255));

    if (!this->backgroundTexture.loadFromFile(this->stateData->localpath+"Images/LS.png"))
        throw "ERROR::LOADING_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
    this->background.setTexture(&this->backgroundTexture);

    title.setFillColor(sf::Color::Black);
    title.setCharacterSize(gui::calcCharSize(vm,20));
    title.setPosition(sf::Vector2f(gui::calcX(30,vm),gui::calcY(40,vm)));
    title.setString("WISIELEC");
    title.setFont(this->font);
    title.setStyle(1);
}


void LoadingState::update(const float& dt)
{
    FadeUpdate(dt);
}


void LoadingState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;
    target->draw(this->background);
    target->draw(title);
    target->draw(fade);
}

void LoadingState::FadeUpdate(const float &dt) {
    if(fadein)
    {
        this->fade.setFillColor(sf::Color(20,20,20,this->fade.getFillColor().a-dt*150.f));
        if(this->fade.getFillColor().a<20) fadein=false;
        time.restart();
    }
    if (time.getElapsedTime().asSeconds() >= 1.5f&& !fadein)
    {
        this->fade.setFillColor(sf::Color(20,20,20,this->fade.getFillColor().a+dt*800.f));
        if(this->fade.getFillColor().a>240)
        {
            auto* temp = new MainMenuState(stateData);
            delete this->states->top();
            this->states->pop();
            this->stateData->states->push(temp);
        }
    }


}
