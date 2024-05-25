#ifndef HANGMAN_LETTERFIELDS_H
#define HANGMAN_LETTERFIELDS_H
#include "Gui.h"
#include <vector>


struct LetterField{
    uint8_t id;
    sf::RectangleShape* floor;
    sf::Text* text;
    float targetAlpha=0;

    LetterField(uint8_t id, sf::RectangleShape* floor, sf::Text* text1):
        id(id),
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
    void initLetterFields(const std::wstring& password);

public:
    //Konstruktor/Destruktor
    LetterFields(const sf::Font& font, GraphicsSettings* settings,const std::wstring& password);
    virtual ~LetterFields();

    //Funkcje
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
    int revealLetter(uint8_t letter);
};


#endif //HANGMAN_LETTERFIELDS_H
