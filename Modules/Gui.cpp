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



gui::Button::Button(float x, float y, float width, float height,
                    sf::Font* font, std::string text, unsigned character_size,float thickness,
                    sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
                    sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color,
                    short unsigned id,
                    float hoverScale,
                    float activeScale
                    )
{
    this->buttonState = BTN_IDLE;
    this->id = id;

    this->hoverScale = hoverScale;
    this->activeScale=activeScale;
    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setOutlineThickness(thickness);
    this->shape.setOutlineColor(outline_idle_color);
    this->shape.setFillColor(sf::Color(255,0,0,0));

    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(text_idle_color);
    this->text.setCharacterSize(character_size);
    this->text.setOrigin(width / 2, height / 2);

    this->text.setPosition(
            this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - (this->text.getGlobalBounds().width / 2.f)+width/2,
            this->shape.getPosition().y+height/2
    );

    this->textIdleColor = text_idle_color;
    this->textHoverColor = text_hover_color;
    this->textActiveColor = text_active_color;

    this->outlineIdleColor = outline_idle_color;
    this->outlineHoverColor = outline_hover_color;
    this->outlineActiveColor = outline_active_color;
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
    if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
    {

        this->buttonState = BTN_HOVER;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            this->buttonState = BTN_ACTIVE;
        }
    }

    float scaleXY;
    switch (this->buttonState)
    {
        case BTN_IDLE:
            scaleXY = lerp(this->text.getScale().x, 1.0f, 8.f*dt);
            this->text.setScale(scaleXY,scaleXY);
            this->text.setFillColor(this->textIdleColor);
            this->shape.setOutlineColor(this->outlineIdleColor);
            break;

        case BTN_HOVER:
            scaleXY = lerp(this->text.getScale().x, hoverScale, 6.5f*dt);
            this->text.setScale(scaleXY,scaleXY);
            this->text.setFillColor(this->textHoverColor);
            this->shape.setOutlineColor(this->outlineHoverColor);
            break;

        case BTN_ACTIVE:
            scaleXY = lerp(this->text.getScale().x, activeScale, 10.f*dt);
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