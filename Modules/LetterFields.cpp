#include "LetterFields.h"
#include "GraphicsSettings.h"
#include <sstream>

std::vector<size_t> findStarPositions(const std::string& str) {
    std::vector<size_t> positions;  // Deklaracja wektora
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == '*') {
            positions.push_back(i);  // Dodawanie pozycji do wektora
        }
    }
    return positions;
}


LetterFields::LetterFields(const sf::Font &font, GraphicsSettings *settings,const std::string& Password) {
    this->font = font;
    this->gfxSettings = settings;
    this->initLetterFields(Password);
}


void LetterFields::initLetterFields(std::string Password) {
    const sf::VideoMode& vm = this->gfxSettings->resolution;

    std::vector<size_t> starPositions = findStarPositions(Password);
    float line=0,pos=0;

    for(int i=0;i<Password.length();i++){

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
                        gui::calcY(20.f-static_cast<float>(starPositions.size()*2), vm) + line * gui::calcY(7, vm)));

                auto *floor = new sf::RectangleShape(sf::Vector2f(
                        gui::calcX(4, vm),
                        gui::calcX(0.3, vm)));

                floor->setPosition(sf::Vector2f(
                        gui::calcX(11.f, vm) + pos * gui::calcX(6, vm),
                        gui::calcY(25.f-static_cast<float>(starPositions.size()*2), vm) + line * gui::calcY(7, vm)));

                floor->setFillColor(sf::Color(70, 70, 70, 255));

                Fields.push_back(new LetterField(
                        false,
                        Password[i],
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



void LetterFields::update(const float& dt) {
    for (auto &it : this->Fields)
    {
        it->text->setFillColor(sf::Color(40,40,40,gui::lerp(it->text->getFillColor().a,it->targetAlpha,dt*3)));
    }
}


void LetterFields::render(sf::RenderTarget *target) {
    for (auto &it : this->Fields)
    {
        target->draw(*it->floor);
        target->draw(*it->text);
    }

}

int LetterFields::revealLetter(char letter) {
    int sum=0;
    for (auto &it : this->Fields)
    {
        if(tolower(it->character)== tolower(letter))
        {
            sum++;
            it->targetAlpha= 255;
        }
    }
    return sum;
}


