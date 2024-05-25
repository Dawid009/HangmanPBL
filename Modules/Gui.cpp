#include "Gui.h"
#include <iostream>

/*****************************************************************************
** Function name:      lerp calcX calcY calcCharSize
** Description:        Funkcje do obliczania interpolacji/rozmiaru na ekranie
*****************************************************************************/
const float gui::lerp(float a, float b, float t) {
    return a + t * (b - a);
}

const float gui::calcX(const float percent, const sf::VideoMode& vm)
{
    return std::floor(static_cast<float>(vm.width) * (percent / 100.f));
}

const float gui::calcY(const float percent, const sf::VideoMode& vm)
{
    return std::floor(static_cast<float>(vm.height) * (percent / 100.f));
}

const unsigned gui::calcCharSize(const sf::VideoMode& vm, const unsigned modifier)
{
    return static_cast<unsigned>((vm.width + vm.height) / modifier);
}

gui::Button::Button(ButtonParams * params) :
    buttonState(BTN_IDLE),
    hoverScale(params->hoverScale),
    activeScale(params->activeScale),
    textIdleColor(params->text_idle_color),
    textHoverColor(params->text_hover_color),
    textActiveColor(params->text_active_color),
    outlineIdleColor(params->outline_idle_color),
    outlineHoverColor(params->outline_hover_color),
    outlineActiveColor(params->outline_active_color),
    enabled(params->initEnable),
    scaleToIdleTime(params->scaleToIdleTime),
    scaleToHoverTime(params->scaleToHoverTime),
    scaleToActiveTime(params->scaleToActiveTime)
{
    if(params->drawDebugBorder){
        outlineIdleColor= sf::Color::Red;
        outlineHoverColor=sf::Color::Red;
        outlineActiveColor=sf::Color::Red;
    }

    if(!params->initEnable){
        outlineIdleColor.a = 70;
        outlineHoverColor.a = 70;
        outlineActiveColor.a = 70;
        textIdleColor.a = 70;
    }

    this->shape.setPosition(sf::Vector2f(params->x,params->y));
    this->shape.setSize(sf::Vector2f(params->width, params->height));
    this->shape.setOutlineThickness(params->thickness);
    this->shape.setOutlineColor(params->outline_idle_color);
    this->shape.setFillColor(sf::Color(255,0,0,0));

    this->text.setFont(*params->font);
    this->text.setString(params->text);
    this->text.setFillColor(params->text_idle_color);
    this->text.setCharacterSize(params->character_size);
    this->text.setOrigin(params->width / 2, params->height / 2);

    this->text.setPosition(
            this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - (this->text.getGlobalBounds().width / 2.f)+params->width/2,
            this->shape.getPosition().y+params->height/2
    );
}

gui::Button::~Button()
{

}

/*****************************************************************************
** Function name:      isPressed
** Description:        Zwraca info czy przycisk jest wcisniety
*****************************************************************************/
const bool gui::Button::isPressed() const
{
    if (this->buttonState == BTN_ACTIVE)
        return true;

    return false;
}


/*****************************************************************************
** Function name:      update
** Description:        Aktualizuje wygląd i sprawdza czy hover/pressed
*****************************************************************************/
void gui::Button::update(const sf::Vector2i& mousePosWindow, const float& dt)
{
    this->buttonState = BTN_IDLE;
    if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)) && this->enabled)
    {

        this->buttonState = BTN_HOVER;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->enabled)
        {
            this->buttonState = BTN_ACTIVE;
        }
    }

    float scaleXY;
    switch (this->buttonState)
    {
        case BTN_IDLE:
            scaleXY = lerp(this->text.getScale().x, 1.0f, this->scaleToIdleTime*dt);
            this->text.setScale(scaleXY,scaleXY);
            this->text.setFillColor(this->textIdleColor);
            this->shape.setOutlineColor(this->outlineIdleColor);
            break;

        case BTN_HOVER:
            scaleXY = lerp(this->text.getScale().x, hoverScale, this->scaleToHoverTime*dt);
            this->text.setScale(scaleXY,scaleXY);
            this->text.setFillColor(this->textHoverColor);
            this->shape.setOutlineColor(this->outlineHoverColor);
            break;

        case BTN_ACTIVE:
            scaleXY = lerp(this->text.getScale().x, activeScale, this->scaleToActiveTime*dt);
            this->text.setScale(scaleXY,scaleXY);
            this->text.setFillColor(this->textActiveColor);
            this->shape.setOutlineColor(this->outlineActiveColor);
            break;
        default:
            this->text.setFillColor(sf::Color::Blue);
            this->shape.setOutlineColor(sf::Color::Green);
            break;
    }
}


/*****************************************************************************
** Function name:      render
** Description:        Renderuje przycisk
*****************************************************************************/
void gui::Button::render(sf::RenderTarget& target)
{
    target.draw(this->shape);
    target.draw(this->text);
}

void gui::Button::ChangeColor(sf::Color color) {
    this->textIdleColor = color;
    this->textHoverColor = sf::Color(std::max(color.r-50,0),std::max(color.g-50,0),std::max(color.b-50,0));
    this->textActiveColor = sf::Color(std::max(color.r-100,0),std::max(color.g-100,0),std::max(color.b-100,0));
}

void gui::Button::SetEnabled(bool enabled) {
    this->enabled = enabled;
    this->textIdleColor.a = 70;
}
