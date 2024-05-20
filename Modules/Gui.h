#ifndef HANGMAN_GUI_H
#define HANGMAN_GUI_H
#include <SFML/Graphics.hpp>

enum button_states{
    BTN_IDLE = 0,
    BTN_HOVER,
    BTN_ACTIVE
};

namespace gui {
    //Funkcje obliczeniowe
    const float lerp(float a, float b, float t);
    const float calcX(const float percent, const sf::VideoMode& vm);
    const float calcY(const float percent, const sf::VideoMode& vm);
    const unsigned calcCharSize(const sf::VideoMode& vm, const unsigned modifier = 60);

    class Button {
    private:
        //Zmienne
        short unsigned buttonState;
        short unsigned id;

        sf::RectangleShape shape;
        sf::Font *font;
        sf::Text text;

        sf::Color textIdleColor;
        sf::Color textHoverColor;
        sf::Color textActiveColor;

        sf::Color outlineIdleColor;
        sf::Color outlineHoverColor;
        sf::Color outlineActiveColor;

        float hoverScale;
        float activeScale;

    public:
        //Konstruktor/Destruktor
        Button(float x, float y, float width, float height,
               sf::Font *font, std::string text, unsigned character_size,float thickness,
               sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
               sf::Color outline_idle_color = sf::Color::Transparent,
               sf::Color outline_hover_color = sf::Color::Transparent,
               sf::Color outline_active_color = sf::Color::Transparent,
               short unsigned id = 0,
               float hoverScale = 1.2f,
               float activeScale = 1.1f
               );
        ~Button();

        //Funkcje
        const bool isPressed() const;
        void update(const sf::Vector2i &mousePosWindow,const float& dt);
        void render(sf::RenderTarget &target);
    };
}
#endif //HANGMAN_GUI_H
