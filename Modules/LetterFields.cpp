#include "LetterFields.h"
#include "GraphicsSettings.h"
#include <sstream>

/*****************************************************************************
** Function name:      findStarPositions
** Description:        Wyszukuje pozycje gwiazdki
*****************************************************************************/
int findStarPositions(const std::string& str) {
    int count=0;// Deklaracja wektora
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == '*') {
            count++;// Dodawanie pozycji do wektora
        }
    }
    return count;
}


LetterFields::LetterFields(const sf::Font &font, GraphicsSettings *settings,const sf::String& Password) {
    this->font = font;
    this->gfxSettings = settings;
    this->initLetterFields(Password);
}

/*****************************************************************************
** Function name:      render
** Description:        Tworzy tekst o określonej ilości pól
*****************************************************************************/
void LetterFields::initLetterFields(const sf::String& Password) {
    const sf::VideoMode& vm = this->gfxSettings->resolution;

    uint8_t starCount = findStarPositions(Password);
    float line=0,pos=0;

    for(int i=0;i<Password.getSize();i++){

        if(Password[i]=='*')
        {
            line++;
            pos=0;
        }else{
            if(Password[i] != ' ') {
                auto *txt = new sf::Text();
                txt->setFont(this->font);
                txt->setString(Password[i]);
                txt->setCharacterSize(gui::calcCharSize(vm,60));

                txt->setFillColor(sf::Color(70, 70, 70, 0));
                txt->setPosition(sf::Vector2f(
                        gui::calcX(11.f , vm) + gui::calcX(0.8, vm) + pos * gui::calcX(6, vm),
                        gui::calcY(20.f-static_cast<float>(starCount*2), vm) + line * gui::calcY(7, vm)));

                auto *floor = new sf::RectangleShape(sf::Vector2f(
                        gui::calcX(4, vm),
                        gui::calcX(0.3, vm)));

                floor->setPosition(sf::Vector2f(
                        gui::calcX(11.f, vm) + pos * gui::calcX(6, vm),
                        gui::calcY(25.f-static_cast<float>(starCount*2), vm) + line * gui::calcY(7, vm)));

                floor->setFillColor(sf::Color(70, 70, 70, 255));

                Fields.push_back(new LetterField(
                        false,
                        sf::String(Password[i]),
                        floor,
                        txt
                ));
            }
            pos++;
        }
    }
}

LetterFields::~LetterFields(){


}


/*****************************************************************************
** Function name:      update
** Description:        Pętla odpowiadająca za aktualizacje zdarzeń
*****************************************************************************/
void LetterFields::update(const float& dt) {
    for (auto &it : this->Fields)
    {
        it->text->setFillColor(sf::Color(40,40,40,gui::lerp(it->text->getFillColor().a,it->targetAlpha,dt*3)));
    }
}

/*****************************************************************************
** Function name:      render
** Description:        Pętla odpowiadająca za wyświetlanie modułu
*****************************************************************************/
void LetterFields::render(sf::RenderTarget *target) {
    for (auto &it : this->Fields)
    {
        target->draw(*it->floor);
        target->draw(*it->text);
    }

}

/*****************************************************************************
** Function name:      revealLetter
** Description:        Podświetla literki jeśli są w tekscie
*****************************************************************************/
int LetterFields::revealLetter(uint8_t letter) {
    uint8_t sum=0;

    sf::String letters = L"AĄBCĆDEĘFGHIJKLŁMNŃOÓPQRSŚTUWXYZŹŻ";

    short letterId=0;
    for (auto &it : this->Fields)
    {
        for(uint_fast8_t i=0;i<letters.getSize();i++){
            if(tolower(it->character[0])==tolower(letters[i]))
            {
                letterId=i;
            }
        }

        if(letterId==letter)
        {
            sum++;
            it->targetAlpha= 255;
        }
    }
    return sum;
}


