#include "Keyboard.h"
#include "GraphicsSettings.h"

Keyboard::Keyboard(const sf::Font& font,GraphicsSettings* settings) {
    this->font = font;
    this->gfxSettings = settings;
    this->initKeyboard();
}


Keyboard::~Keyboard() {
    delete gfxSettings;
    for (auto &it : this->buttons)
    {
        delete it.second;
    }
}


void Keyboard::initKeyboard() {
    const sf::VideoMode& vm = this->gfxSettings->resolution;

    auto* ButtonInitParams = new gui::ButtonParams;

    ButtonInitParams->width = static_cast<float>(gui::calcCharSize(vm,40));
    ButtonInitParams->height = static_cast<float>(gui::calcCharSize(vm,50));
    ButtonInitParams->font = &this->font;
    ButtonInitParams->thickness = 2.f;
    ButtonInitParams->character_size = gui::calcCharSize(vm,60);
    ButtonInitParams->hoverScale = 2.0f;
    ButtonInitParams->activeScale = 1.5f;
    ButtonInitParams->text_idle_color=sf::Color(30,30,30,255);

    constexpr wchar_t letters[35] = L"AĄBCĆDEĘFGHIJKLŁMNŃOÓPQRSŚTUWXYZŹŻ";

    uint8_t id=0;
    uint8_t line=0,pos=0;
    for(auto ch : letters){
        if(pos<10){
            ButtonInitParams->x =  gui::calcX(10,vm)+static_cast<float>(pos)*gui::calcX(5.1f,vm);
            ButtonInitParams->y =  gui::calcY(55,vm)+static_cast<float>(line)*gui::calcY(8.f,vm);
            ButtonInitParams->text = sf::String(ch);
            buttons[id] = new gui::Button(ButtonInitParams);
            pos++;
        }else{
            pos=0;
            line++;
            ButtonInitParams->x =  gui::calcX(10,vm)+static_cast<float>(pos)*gui::calcX(5.1f,vm);
            ButtonInitParams->y =  gui::calcY(55,vm)+static_cast<float>(line)*gui::calcY(8.f,vm);
            ButtonInitParams->text = sf::String(ch);
            buttons[id] = new gui::Button(ButtonInitParams);
            pos++;
        }
        id++;
    }

    //przeniesc gdzie indziej
    ButtonInitParams->x =  gui::calcX(90,vm);
    ButtonInitParams->y =  gui::calcY(90,vm);
    ButtonInitParams->text = sf::String("Menu");
    ButtonInitParams->text_idle_color = sf::Color::White;
    ButtonInitParams->text_hover_color = sf::Color::White;
    ButtonInitParams->text_active_color = sf::Color::White;
    buttons[L'*'] = new gui::Button(ButtonInitParams);

    delete ButtonInitParams;
}


void Keyboard::updateButtons(const sf::Vector2i& mousePosWindow,const float& dt)
{
    for (auto &it : this->buttons)
    {
        it.second->update(mousePosWindow,dt);
    }
}


void Keyboard::update(const sf::Vector2i& mousePosWindow,const float& dt)
{
    this->updateButtons(mousePosWindow,dt);
}


void Keyboard::render(sf::RenderTarget *target) {

    //Renderowanie buttonów
    for (auto &it : this->buttons)
    {
        it.second->render(*target);
    }
}


void Keyboard::SetButtonEnabled(uint8_t key,bool enabled) {
    buttons[key]->SetEnabled(enabled);
}


void Keyboard::SetButtonColor(uint8_t key,sf::Color color) {
    buttons[key]->ChangeColor(color);

}


const bool Keyboard::IsPressed(uint8_t key) {
    if (this->buttons[key]->isPressed()) {
        return true;
    } else
    {
        return false;
    }
}
