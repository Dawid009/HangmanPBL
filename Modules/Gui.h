#ifndef HANGMAN_GUI_H
#define HANGMAN_GUI_H
#include <SFML/Graphics.hpp>

enum button_states{
    BTN_IDLE = 0,
    BTN_HOVER,
    BTN_ACTIVE
};

namespace gui {
    struct ButtonParams {
        float x=20.f;
        float y=20.f;
        float width=50.f;
        float height=50.f;
        sf::Font* font;
        sf::String text = "";
        unsigned character_size = 10;
        float thickness = 3.f;
        sf::Color text_idle_color = sf::Color(70,70,70,255);
        sf::Color text_hover_color = sf::Color(40,40,40,255);
        sf::Color text_active_color = sf::Color(20,20,20,255);
        sf::Color outline_idle_color = sf::Color::Transparent;
        sf::Color outline_hover_color = sf::Color::Transparent;
        sf::Color outline_active_color = sf::Color::Transparent;
        short unsigned id=1;
        float hoverScale=1.2f;
        float activeScale=1.1f;
        float scaleToIdleTime=8.f;
        float scaleToHoverTime=6.5f;
        float scaleToActiveTime=10.f;
        bool drawDebugBorder=false;
        bool initEnable=true;
    };

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

        float scaleToIdleTime;
        float scaleToHoverTime;
        float scaleToActiveTime;

        bool enabled;

    public:
        //Konstruktor/Destruktor
        Button(ButtonParams * params);
        ~Button();

        //Funkcje
        const bool isPressed() const;
        void update(const sf::Vector2i &mousePosWindow,const float& dt);
        void render(sf::RenderTarget &target);
        void SetEnabled(bool enabled);
        void ChangeColor(sf::Color color);
    };
}
#endif //HANGMAN_GUI_H
