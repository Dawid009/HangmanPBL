#include "Transition.h"
#include "GraphicsSettings.h"
#include "Gui.h"
#include "../States/GameState.h"

Transition::Transition(state)
{
    const sf::VideoMode& vm = state_data->gfxSettings->resolution;

    transitionScreen = new sf::RectangleShape(sf::Vector2f(vm.width,vm.height));
    transitionScreen->setFillColor(sf::Color(20,20,20,255));
}

Transition::~Transition() {
    delete transitionScreen;
}

void Transition::update(const float &dt) {
    this->transitionScreen->setFillColor(sf::Color(0,0,0,gui::lerp(this->transitionScreen->getFillColor().a, 0, dt*1)));

        this->transitionScreen->setFillColor(sf::Color(20,20,20,gui::lerp(this->transitionScreen->getFillColor().a, 276, dt*6)));
        std::cout<<static_cast<float>(this->transitionScreen->getFillColor().a)<<std::endl;

    if(this->transitionScreen->getFillColor().a==254){


}

void Transition::render(sf::RenderTarget *target) {
    if(target!= nullptr && transitionScreen!= nullptr)
        target->draw(*transitionScreen);
}
