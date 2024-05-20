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
    const int colorIdle = 40;
    const int colorHover = 30;
    const int colorActive = 20;
    //od 65
    int letter = 65;
    for(int i=0;i<3;i++){
        for(int j=0;j<10&&letter<91;j++){
            buttons[(char)letter] = new gui::Button(
                    gui::calcX(10,vm)+j*gui::calcX(5.1f,vm),
                    gui::calcY(55,vm)+i*gui::calcY(8.f,vm),
                    static_cast<float>(gui::calcCharSize(vm,40)),
                    static_cast<float>(gui::calcCharSize(vm,50)),
                    &this->font,std::string(1,(char)letter),gui::calcCharSize(vm,60),2.f,
                    sf::Color(colorIdle, colorIdle, colorIdle, 255),
                    sf::Color(colorHover, colorHover, colorHover, 255),
                    sf::Color(colorActive, colorActive, colorActive, 255),
                    sf::Color::Transparent,
                    sf::Color::Transparent,
                    sf::Color::Transparent,
                    1,2.5f,1.8f
            );
            letter++;
        }
    }
}


void Keyboard::updateButtons(const sf::Vector2i& mousePosWindow,const float& dt)
{
    for (auto &it : this->buttons)
    {
        it.second->update(mousePosWindow,dt);
    }

    //Nowa gra
    if (this->buttons['A']->isPressed())
    {
        //dodać do buttonów is disabled?
        std::cout<<"A pressed!"<<std::endl;
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



