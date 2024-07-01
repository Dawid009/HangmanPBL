#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::VideoMode& vm, sf::Font& font)
        : font(font)
{
    this->background.setSize(sf::Vector2f(static_cast<float>(vm.width),static_cast<float>(vm.height)));
    this->background.setFillColor(sf::Color(20, 20, 20, 100));
    this->container.setSize(sf::Vector2f(static_cast<float>(vm.width) / 4.f,static_cast<float>(vm.height) - gui::calcY(9.3f, vm)));
    this->container.setFillColor(sf::Color(20, 20, 20, 200));
    this->container.setPosition(static_cast<float>(vm.width) / 2.f - this->container.getSize().x / 2.f,30.f);

    this->menuText.setFont(font);
    this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
    this->menuText.setCharacterSize(gui::calcCharSize(vm));
    this->menuText.setString("ZATRZYMANO");
    this->menuText.setPosition(
            this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
            this->container.getPosition().y + gui::calcY(4.f, vm)
    );
}

PauseMenu::~PauseMenu()
{
    for (auto &it : this->buttons)
        delete it.second;
}

bool PauseMenu::isButtonPressed(const std::string& key)
{
    return this->buttons[key]->isPressed();
}

void PauseMenu::addButton(
        const std::string& key,
        const float y,
        const float width,
        const float height,
        const unsigned char_size,
        const std::wstring& text)
{
    float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

    auto* ButtonInitParams = new gui::ButtonParams;
    ButtonInitParams->x =  x;
    ButtonInitParams->y =  y;
    ButtonInitParams->width = width;
    ButtonInitParams->height = height;
    ButtonInitParams->font = &this->font;
    ButtonInitParams->text = text;
    ButtonInitParams->text_idle_color = sf::Color(180,180,180,255);
    ButtonInitParams->text_hover_color = sf::Color::White;
    ButtonInitParams->text_active_color = sf::Color::White;
    ButtonInitParams->character_size = char_size;
    ButtonInitParams->hoverScale = 1.2f;
    ButtonInitParams->activeScale = 1.1f;

    this->buttons[key] = new gui::Button(ButtonInitParams);
    delete ButtonInitParams;
}

void PauseMenu::update(const sf::Vector2i& mousePosWindow,const float& dt)
{
    for (auto &i : this->buttons)
        i.second->update(mousePosWindow,dt);
}

void PauseMenu::render(sf::RenderTarget & target)
{
    target.draw(this->background);
    target.draw(this->container);

    for (auto &i : this->buttons)
        i.second->render(target);

    target.draw(this->menuText);
}