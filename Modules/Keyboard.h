#ifndef HANGMAN_KEYBOARD_H
#define HANGMAN_KEYBOARD_H
#include "Gui.h"

class Keyboard {
private:
    //Zmienne
    std::map<char, gui::Button*> buttons;
    sf::Font font;
    class GraphicsSettings* gfxSettings;

    //Funkcje
    void initKeyboard();
public:
    //Konstruktor/Destruktor
    Keyboard(const sf::Font& font, GraphicsSettings* settings);
    virtual ~Keyboard();

    //Funkcje
    void SetButtonEnabled(char key,bool enabled);
    void SetButtonColor(char key,sf::Color color);
    const bool IsPressed(char key);
    void updateButtons(const sf::Vector2i& mousePosWindow,const float& dt);
    void update(const sf::Vector2i& mousePosWindow,const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};


#endif //HANGMAN_KEYBOARD_H
