#include "Keyboard.h"
#include "GraphicsSettings.h"

Keyboard::Keyboard(const sf::Font& font,GraphicsSettings* settings) {
    this->font = font;
    this->gfxSettings = settings;
    this->initKeyboard();
}

Keyboard::~Keyboard() {

}

/*****************************************************************************
** Function name:      initKeyboard
** Description:        Tworzy grid z przycisków
*****************************************************************************/
void Keyboard::initKeyboard() {
    const sf::VideoMode& vm = this->gfxSettings->resolution;

    auto* ButtonInitParams = new gui::ButtonParams;

    ButtonInitParams->width = static_cast<float>(gui::calcCharSize(vm,40));
    ButtonInitParams->height = static_cast<float>(gui::calcCharSize(vm,50));
    ButtonInitParams->font = &this->font;
    ButtonInitParams->thickness = 2.f;
    ButtonInitParams->character_size = gui::calcCharSize(vm,60);
    ButtonInitParams->hoverScale = 2.5f;
    ButtonInitParams->activeScale = 1.8f;

    char letter = 65; //65 to A
    for(int i=0;i<3;i++){
        for(int j=0;j<10&&letter<91;j++){
            ButtonInitParams->x =  gui::calcX(10,vm)+j*gui::calcX(5.1f,vm);
            ButtonInitParams->y =  gui::calcY(55,vm)+i*gui::calcY(8.f,vm);
            ButtonInitParams->text = std::string(1,letter);
            buttons[letter] = new gui::Button(ButtonInitParams);
            letter++;
        }
    }
    delete ButtonInitParams;
}

/*****************************************************************************
** Function name:      updateButtons
** Description:        Wywoluje aktualizacje zdarzeń dla kazdego przycisku
*****************************************************************************/
void Keyboard::updateButtons(const sf::Vector2i& mousePosWindow,const float& dt)
{
    for (auto &it : this->buttons)
    {
        it.second->update(mousePosWindow,dt);
    }
}

/*****************************************************************************
** Function name:      update
** Description:        Pętla modułu odpowiadająca za zdarzenia
*****************************************************************************/
void Keyboard::update(const sf::Vector2i& mousePosWindow,const float& dt)
{
    this->updateButtons(mousePosWindow,dt);


}

/*****************************************************************************
** Function name:      render
** Description:        Pętla odpowiadająca za wyświetlanie
*****************************************************************************/
void Keyboard::render(sf::RenderTarget *target) {

    //Renderowanie buttonów
    for (auto &it : this->buttons)
    {
        it.second->render(*target);
    }
}

/*****************************************************************************
** Function name:      SetButton Enabled, Color
** Description:        Ustawianie koloru, wylaczanie przycisku
*****************************************************************************/
void Keyboard::SetButtonEnabled(char key,bool enabled) {
    buttons[key]->SetEnabled(enabled);
}

void Keyboard::SetButtonColor(char key,sf::Color color) {
    buttons[key]->ChangeColor(color);

}

/*****************************************************************************
** Function name:      isPressed
** Description:        Zwraca aktualny stan dla danego przycisku
*****************************************************************************/
const bool Keyboard::IsPressed(char key) {
    if (this->buttons[key]->isPressed()) {
        return true;
    } else
    {
        return false;
    }
}
