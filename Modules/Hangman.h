#ifndef HANGMAN_HANGMAN_H
#define HANGMAN_HANGMAN_H
#include "Gui.h"

class Hangman {

private:
    class GraphicsSettings* gfxSettings;
    sf::RenderTexture* renderTexture;
    sf::Sprite* sprite;
    sf::RectangleShape* line;
    sf::Shape* hangman_parts[6];

    void initHangman();
public:
    //Konstruktor/Destruktor
    Hangman(GraphicsSettings *settings);
    virtual ~Hangman();
    void setLevel(uint8_t level);
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};


#endif //HANGMAN_HANGMAN_H
