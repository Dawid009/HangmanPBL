#include "LetterFields.h"
#include "GraphicsSettings.h"
#include <sstream>

/*****************************************************************************
** Function name:      findStarPositions
** Description:        Wyszukuje pozycje gwiazdki
*****************************************************************************/
int findStarPositions(const std::wstring& str) {
    int count=0;
    for (size_t i = 0; i < str.length(); ++i) {
        if (str[i] == '*') {
            count++;
        }
    }
    return count;
}


LetterFields::LetterFields(const sf::Font &font, GraphicsSettings *settings,const std::wstring& password) {
    this->font = font;
    this->gfxSettings = settings;
    this->initLetterFields(password);
}

LetterFields::~LetterFields(){
    //Zwalnianie pamięci
    delete gfxSettings;
    for(auto field : Fields){
        delete field;
    }
}



/*****************************************************************************
** Function name:      render
** Description:        Tworzy tekst o określonej ilości pól
*****************************************************************************/
void LetterFields::initLetterFields(const std::wstring& password) {
    const sf::VideoMode& vm = this->gfxSettings->resolution;

    uint8_t starCount = findStarPositions(password);
    float line=0,pos=0;

    for(int i=0;i<password.size();i++){

        if(password[i]==L'*')
        {
            line++;
            pos=0;
        }else{
            if(password[i] != L' ') {
                auto *txt = new sf::Text();
                txt->setFont(this->font);
                txt->setString(password[i]);
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

                constexpr wchar_t letters[35] = L"AĄBCĆDEĘFGHIJKLŁMNŃOÓPQRSŚTUWXYZŹŻ";
                for(uint_fast8_t j=0;j<35;j++){
                    if(tolower(password[i])==tolower(letters[j]))
                    {
                        Fields.push_back(new LetterField(
                                j,
                                floor,
                                txt
                        ));
                    }
                }
            }
            pos++;
        }
    }

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
int LetterFields::revealLetter(const uint8_t letter) {
    uint8_t sum=0;
    for (auto &it : this->Fields)
    {
        if(it->id==letter)
        {
            sum++;
            it->targetAlpha= 255;
        }
    }
    return sum;
}


