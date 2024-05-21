#ifndef HANGMAN_LETTERFIELDS_H
#define HANGMAN_LETTERFIELDS_H
#include "Gui.h"
#include <vector>


struct LetterField{
    bool isVisible;
    sf::String character;
    sf::RectangleShape* floor;
    sf::Text* text;
    float currentAlpha=0;
    float targetAlpha=0;

    LetterField(bool isVisible, sf::String character, sf::RectangleShape* floor, sf::Text* text1):
        isVisible(isVisible),
        character(character),
        floor(floor),
        text(text1)
        {}
};


class LetterFields {
private:
    //Zmienne
    std::vector<LetterField*> Fields;
    class GraphicsSettings* gfxSettings;
    sf::Font font;

    //Funkcje
    void initLetterFields(const sf::String& Password);

public:
    //Konstruktor/Destruktor
    LetterFields(const sf::Font& font, GraphicsSettings* settings,const sf::String& Password);
    virtual ~LetterFields();

    //Funkcje
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
    int revealLetter(uint8_t letter);
};


#endif //HANGMAN_LETTERFIELDS_H
