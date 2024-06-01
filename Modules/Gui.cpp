#include "Gui.h"
#include <iostream>


bool gui::Button::mousePressed = false;

float gui::lerp(float a, float b, float t) {
    return a + t * (b - a);
}

float gui::calcX(const float percent, const sf::VideoMode &vm) {
    return std::floor(static_cast<float>(vm.width) * (percent / 100.f));
}

float gui::calcY(const float percent, const sf::VideoMode &vm) {
    return std::floor(static_cast<float>(vm.height) * (percent / 100.f));
}

unsigned gui::calcCharSize(const sf::VideoMode &vm, const unsigned modifier) {
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
    backgroundIdleColor(params->background_idle_color),
    backgroundHoverColor(params->background_hover_color),
    backgroundActiveColor(params->background_active_color),
    enabled(params->initEnable),
    scaleToIdleTime(params->scaleToIdleTime),
    scaleToHoverTime(params->scaleToHoverTime),
    scaleToActiveTime(params->scaleToActiveTime),
    id(params->id)
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
    this->shape.setFillColor(backgroundIdleColor);

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

gui::Button::~Button() = default;

bool gui::Button::isPressed() const
{
    if (this->buttonState == BTN_ACTIVE)
        return true;

    return false;
}


void gui::Button::update(const sf::Vector2i& mousePosWindow, const float& dt)
{
    this->buttonState = BTN_IDLE;

    if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        mousePressed=false;
    }

    if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)) && this->enabled)
    {

        this->buttonState = BTN_HOVER;
        if (!mousePressed && sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->enabled) {
            this->buttonState = BTN_ACTIVE;
            mousePressed=true;
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
            this->shape.setFillColor(backgroundIdleColor);
            break;

        case BTN_HOVER:
            scaleXY = lerp(this->text.getScale().x, hoverScale, this->scaleToHoverTime*dt);
            this->text.setScale(scaleXY,scaleXY);
            this->text.setFillColor(this->textHoverColor);
            this->shape.setOutlineColor(this->outlineHoverColor);
            this->shape.setFillColor(backgroundHoverColor);
            break;

        case BTN_ACTIVE:
            scaleXY = lerp(this->text.getScale().x, activeScale, this->scaleToActiveTime*dt);
            this->text.setScale(scaleXY,scaleXY);
            this->text.setFillColor(this->textActiveColor);
            this->shape.setOutlineColor(this->outlineActiveColor);
            this->shape.setFillColor(backgroundActiveColor);
            break;
        default:
            this->text.setFillColor(sf::Color::Blue);
            this->shape.setOutlineColor(sf::Color::Green);
            break;
    }
}


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

void gui::Button::SetEnabled(bool enable) {
    this->enabled = enable;
    this->textIdleColor.a = 70;
}



std::string gui::Button::getText() const
{
    return this->text.getString();
}

const short unsigned & gui::Button::getId() const
{
    return this->id;
}

//Modifiers
void gui::Button::setText(const std::string& text)
{
    this->text.setString(text);
}

void gui::Button::setId(short unsigned id)
{
    this->id = id;
}



gui::DropDownList::DropDownList(DropDownParams* params)
        : font(*params->font), showList(false), keytimeMax(1.f), keytime(0.f)
{
    auto* ButtonInitParams = new gui::ButtonParams;
    ButtonInitParams->x =  params->x;
    ButtonInitParams->y =  params->y;
    ButtonInitParams->width = params->width;
    ButtonInitParams->height = params->height;
    ButtonInitParams->font = &font;
    ButtonInitParams->text = params->list[params->id];
    ButtonInitParams->text_idle_color = sf::Color::White;
    ButtonInitParams->text_hover_color = sf::Color::White;
    ButtonInitParams->text_active_color = sf::Color::White;
    ButtonInitParams->character_size = params->character_size;
    ButtonInitParams->hoverScale = 1.2f;
    ButtonInitParams->activeScale = 1.1f;
    ButtonInitParams->background_idle_color = sf::Color(255, 255, 255, 200);
    ButtonInitParams->background_hover_color = sf::Color(255, 255, 255, 255);
    ButtonInitParams->id = params->id;

    this->activeElement = new gui::Button(ButtonInitParams);

    for (unsigned i = 0; i < params->nrOfElements; i++)
    {
        ButtonInitParams->y =  params->y + ((static_cast<float>(i)+1) * params->height);
        ButtonInitParams->text = params->list[i];
        ButtonInitParams->id = i;
        this->list.push_back(
                new gui::Button(ButtonInitParams)
        );
    }
}

gui::DropDownList::~DropDownList()
{
    delete this->activeElement;
    for (auto el : this->list)
    {
        delete el;
    }
}

bool gui::DropDownList::getKeytime()
{
    if (this->keytime >= this->keytimeMax)
    {
        this->keytime = 0.f;
        return true;
    }

    return false;
}

const unsigned short & gui::DropDownList::getActiveElementId() const
{
    return this->activeElement->getId();
}


void gui::DropDownList::update(const sf::Vector2i & mousePosWindow, const float& dt)
{
    //update keytime
    if (this->keytime < this->keytimeMax)
        this->keytime += 10.f * dt;

    this->activeElement->update(mousePosWindow,dt);


    if (this->activeElement->isPressed() && this->getKeytime())
    {
        if (this->showList)
            this->showList = false;
        else
            this->showList = true;
    }

    if (this->showList)
    {
        for (auto &i : this->list)
        {
            i->update(mousePosWindow,dt);

            if (i->isPressed() && this->getKeytime())
            {
                this->showList = false;
                this->activeElement->setText(i->getText());
                this->activeElement->setId(i->getId());
            }
        }
    }
}

void gui::DropDownList::render(sf::RenderTarget & target)
{
    this->activeElement->render(target);

    if (this->showList)
    {
        for (auto &i : this->list)
        {
            i->render(target);
        }
    }
}