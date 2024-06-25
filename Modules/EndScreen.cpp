#include "EndScreen.h"


EndScreen::EndScreen(sf::VideoMode& vm, sf::Font& font)
        : font(font)
{
    this->background.setSize(sf::Vector2f(static_cast<float>(vm.width),static_cast<float>(vm.height)));
    this->background.setFillColor(sf::Color(20, 20, 20, 140));
    this->container.setSize(sf::Vector2f(static_cast<float>(vm.width) / 2.f,static_cast<float>(vm.height)/2));
    this->container.setFillColor(sf::Color(20, 20, 20, 200));
    this->container.setPosition(static_cast<float>(vm.width) / 2.f - this->container.getSize().x / 2.f,static_cast<float>(vm.height) / 4.f);


    this->menuText.setFont(font);
    this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
    this->menuText.setCharacterSize(gui::calcCharSize(vm)*2.5);
    this->menuText.setString("Koniec Gry");
    this->menuText.setPosition(
            this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
            this->container.getPosition().y + gui::calcY(4.f, vm)
    );

    this->winText.setFont(font);
    this->winText.setFillColor(sf::Color(150, 155, 155, 200));
    this->winText.setCharacterSize(gui::calcCharSize(vm)*1.7f);
    this->winText.setString(L"Wygrałeś!");
    this->winText.setPosition(
            this->container.getPosition().x + this->container.getSize().x / 2.f - this->winText.getGlobalBounds().width / 2.f,
            this->container.getPosition().y + gui::calcY(15.f, vm)
    );

    this->loseText.setFont(font);
    this->loseText.setFillColor(sf::Color(155, 155, 155, 200));
    this->loseText.setCharacterSize(gui::calcCharSize(vm)*1.7f);
    this->loseText.setString(L"Przegrałeś!");
    this->loseText.setPosition(
            this->container.getPosition().x + this->container.getSize().x / 2.f - this->loseText.getGlobalBounds().width / 2.f,
            this->container.getPosition().y + gui::calcY(15.f, vm)
    );

    auto* ButtonInitParams = new gui::ButtonParams;
    ButtonInitParams->y =  this->container.getPosition().y + gui::calcY(35.f, vm);
    ButtonInitParams->width = gui::calcX(10.f, vm);

    float x = this->container.getPosition().x + this->container.getSize().x / 3.f * 2 - ButtonInitParams->width  / 2.f;
    ButtonInitParams->x = x;

    ButtonInitParams->height = gui::calcY(6.f, vm);;
    ButtonInitParams->font = &this->font;
    ButtonInitParams->text = "Wyjdz";
    ButtonInitParams->text_idle_color = sf::Color(180,180,180,255);
    ButtonInitParams->text_hover_color = sf::Color::White;
    ButtonInitParams->text_active_color = sf::Color::White;
    ButtonInitParams->character_size = gui::calcCharSize(vm);
    ButtonInitParams->hoverScale = 1.2f;
    ButtonInitParams->activeScale = 1.1f;

    this->buttons["QUIT"] = new gui::Button(
            ButtonInitParams
    );
    x = this->container.getPosition().x + this->container.getSize().x / 3.f - ButtonInitParams->width  / 2.f;
    ButtonInitParams->x = x;
    ButtonInitParams->text = "Nowa gra";

    this->buttons["NEW"] = new gui::Button(
            ButtonInitParams
    );

    delete ButtonInitParams;
}

EndScreen::~EndScreen()
{
    for (auto &it : this->buttons)
    {
        delete it.second;
    }
}

bool EndScreen::isButtonPressed(const std::string& key)
{
    return this->buttons[key]->isPressed();
}


void EndScreen::update(const sf::Vector2i& mousePosWindow,const float& dt)
{
    for (auto &i : this->buttons)
    {
        i.second->update(mousePosWindow,dt);
    }
}

void EndScreen::render(sf::RenderTarget & target)
{
    target.draw(this->background);
    target.draw(this->container);

    if(win){
        target.draw(winText);
    }else{
        target.draw(loseText);
    }

    for (auto &i : this->buttons)
    {
        i.second->render(target);
    }

    target.draw(this->menuText);
}