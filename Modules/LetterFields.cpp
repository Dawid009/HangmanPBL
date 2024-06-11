#include "LetterFields.h"
#include "GraphicsSettings.h"
#include <sstream>

int findStarPositions(const std::wstring& str) {
    int count{0};
    for (size_t i{0}; i < str.length(); ++i) {
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


void LetterFields::initLetterFields(const std::wstring& password) {
    const sf::VideoMode& vm = this->gfxSettings->resolution;

    uint8_t starCount = findStarPositions(password);
    float line{0},pos{0};

    for(int i{0};i<password.size();i++)
    {
        if(password[i]==L'*')
        {
            line++;
            pos=0;
        }else
        {
            if(password[i] != L' ')
            {
                auto *txt = new sf::Text();
                txt->setFont(this->font);
                txt->setString(password[i]);
                txt->setCharacterSize(gui::calcCharSize(vm,50));

                txt->setFillColor(sf::Color(70, 70, 70, 0));
                txt->setPosition(sf::Vector2f(
                        gui::calcX(7.f , vm) + gui::calcX(0.8, vm) + pos * gui::calcX(6, vm),
                        gui::calcY(19.4f-static_cast<float>(starCount*2), vm) + line * gui::calcY(7, vm)));

                auto *floor = new sf::RectangleShape(sf::Vector2f(
                        gui::calcX(4, vm),
                        gui::calcX(0.3, vm)));

                floor->setPosition(sf::Vector2f(
                        gui::calcX(7.f, vm) + pos * gui::calcX(6, vm),
                        gui::calcY(25.f-static_cast<float>(starCount*2), vm) + line * gui::calcY(7, vm)));

                 floor->setFillColor(sf::Color(70, 70, 70, 255));

                constexpr wchar_t letters[35] = L"AĄBCĆDEĘFGHIJKLŁMNŃOÓPQRSŚTUWXYZŹŻ";
                for(uint_fast8_t j{0};j<35;j++){
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


void LetterFields::update(const float& dt) {
    for (auto &it : this->Fields)
    {
        it->text->setFillColor(sf::Color(40,40,40,static_cast<sf::Uint8>(gui::lerp(it->text->getFillColor().a,it->targetAlpha,dt*3))));
    }
}


void LetterFields::render(sf::RenderTarget *target) {
    for (auto &it : this->Fields)
    {
        target->draw(*it->floor);
        target->draw(*it->text);
    }

}


int LetterFields::revealLetter(const uint8_t letter) {
    uint8_t sum{0};
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


