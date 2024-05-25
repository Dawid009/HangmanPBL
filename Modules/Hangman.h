#ifndef HANGMAN_HANGMAN_H
#define HANGMAN_HANGMAN_H
#include "Gui.h"

class Hangman {

private:
    class GraphicsSettings* gfxSettings;
    sf::RenderTexture* renderTexture;
    sf::Sprite* sprite;

    //do line nie trzeba dostepu, zmienic calosc na wektor
    sf::RectangleShape* line;
    sf::CircleShape* head;
    sf::RectangleShape* body;
    sf::RectangleShape* arm1;
    sf::RectangleShape* arm2;
    sf::RectangleShape* leg1;
    sf::RectangleShape* leg2;

    void initHangman();
public:
    //Konstruktor/Destruktor
    Hangman(GraphicsSettings *settings);
    virtual ~Hangman();
    void setLevel(short level);
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};


#endif //HANGMAN_HANGMAN_H
