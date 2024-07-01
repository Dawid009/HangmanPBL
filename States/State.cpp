#include "State.h"

State::State(StateData* state_data) :
    stateData(state_data),
    window(state_data->window),
    states(state_data->states),
    stateptr(nullptr),
    quit(false)
{}

State::~State() = default;

const bool & State::getQuit() const
{
    return this->quit;
}

void State::updateMousePositions(sf::View* view)
{
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
}

void State::endState()
{
    this->quit = true;
}

void State::FadeUpdate(const float& dt) {
    if(fadein)
    {
        this->fade.setFillColor(sf::Color(20,20,20,this->fade.getFillColor().a-dt*1000));
        if(this->fade.getFillColor().a<20)
            fadein=false;

    }

    if (!pushedNew && stateptr!= nullptr)
    {
        this->fade.setFillColor(sf::Color(20,20,20,this->fade.getFillColor().a+dt*900));
        if(this->fade.getFillColor().a>240)
        {
            pushedNew=true;
            this->states->pop();
            this->stateData->states->push(stateptr);
        }
    }
}

void State::initDeferredRender()
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

void State::initFonts()
{
    if (!this->font.loadFromFile(this->stateData->localpath+"Fonts/Caveat.ttf"))
    {
        throw("ERROR: Nie udalo sie zaladowac czcionki");
    }
    std::locale::global(std::locale("pl_PL.UTF-8"));
}
