/**
 * @file Gui.h
 * @brief User interface elements
 */

#ifndef HANGMAN_GUI_H
#define HANGMAN_GUI_H
#include <SFML/Graphics.hpp>

/**
 * @enum button_states
 * @brief The states that the button can take
 */
enum button_states{
    BTN_IDLE = 0,
    BTN_HOVER,
    BTN_ACTIVE
};


namespace gui {

    /**
    * @struct ButtonParams
    * @brief Options when creating a button
    */
    struct ButtonParams {
        float x=20.f; ///<Button position x
        float y=20.f; ///<Button position y
        float width=50.f; ///<Button width
        float height=50.f; ///<Button height
        sf::Font* font; ///<Pointer to any font
        sf::String text = ""; ///<Text to be displayed on the button
        unsigned character_size = 10; ///<Text character size
        float thickness = 3.f; ///<Button outline thickness
        sf::Color text_idle_color = sf::Color(70,70,70,255); ///<Text idle color
        sf::Color text_hover_color = sf::Color(40,40,40,255);///<Text color when hovered
        sf::Color text_active_color = sf::Color(20,20,20,255);///<Text color when pressed
        sf::Color outline_idle_color = sf::Color::Transparent; ///<Outline idle color
        sf::Color outline_hover_color = sf::Color::Transparent;///<Outline color when hovered
        sf::Color outline_active_color = sf::Color::Transparent;///<Outline color when pressed
        float hoverScale=1.2f; ///<Scale of button when hovered
        float activeScale=1.1f;///<Scale of button when pressed
        float scaleToIdleTime=8.f;///<Scale time required to transit to idle
        float scaleToHoverTime=6.5f;///<Scale time required to transit to hover
        float scaleToActiveTime=10.f;///<Scale time required to transit to idle
        bool drawDebugBorder=false;///<Should draw red button border
        bool initEnable=true;///<Should button be enabled
    };

    /**
    * @brief Class constructor
    * @param a Current value
    * @param b The value to which the function is going
    * @param t Speed modifier
    * @returns Returns the value for a given iteration
    */
    const float lerp(float a, float b, float t);
    /**
    * @brief Based on the percentage of the window, calculates the value of X
    * @param percent Percentage of screen from point 0
    * @param vm Pointer to VideoMode
    * @returns Returns the X value
    */
    const float calcX(const float percent, const sf::VideoMode& vm);
    /**
    * @brief Based on the percentage of the window, calculates the value of Y
    * @param percent Percentage of screen from point 0
    * @param vm Pointer to VideoMode
    * @returns Returns the Y value
    */
    const float calcY(const float percent, const sf::VideoMode& vm);
    /**
    * @brief Calculates character size on the screen
    * @param vm Pointer to VideoMode
    * @param modifier Char size modifier
    * @returns Returns character size value
    */
    const unsigned calcCharSize(const sf::VideoMode& vm, const unsigned modifier = 60);


    /**
    * @class Button
    * @brief Class representing a button on the screen
    */
    class Button {
    private:
        short unsigned buttonState;///<Current state of the button

        sf::RectangleShape shape; ///<SFML rectangle
        sf::Text text; ///<Text to be displayed on the button

        sf::Color textIdleColor;  ///<Text idle color
        sf::Color textHoverColor; ///<Text color when hovered
        sf::Color textActiveColor;///<Text color when pressed

        sf::Color outlineIdleColor;///<Outline idle color
        sf::Color outlineHoverColor;///<Outline color when hovered
        sf::Color outlineActiveColor;///<Outline color when pressed

        float hoverScale;///<Scale of button when hovered
        float activeScale;///<Scale of button when pressed

        float scaleToIdleTime;///<Scale time required to transit to idle
        float scaleToHoverTime;///<Scale time required to transit to hover
        float scaleToActiveTime;///<Scale time required to transit to idle

        bool enabled;///<Should button be enabled

    public:
        /**
        * @brief Class constructor
        * @param params Object with all button settings
        */
        Button(ButtonParams * params);

        /**
        * @brief Class destructor
        */
        ~Button();

        /**
        * @brief Checks if the button is pressed
        * @return Returns a logical yes or no
        */
        const bool isPressed() const;

        /**
        * @brief Sets the button to on or off
        * @param enabled Should be enabled?
        */
        void SetEnabled(bool enabled);

        /**
        * @brief Sets the button to a given color
        * @param color Color
        */
        void ChangeColor(sf::Color color);

        /**
        * @brief Main module loop updating events
        * @param dt Delta time value
        */
        void update(const sf::Vector2i &mousePosWindow,const float& dt);

        /**
        * @brief Loop for rendering
        * @param target Pointer to the renderer
        */
        void render(sf::RenderTarget &target);

    };
}
#endif //HANGMAN_GUI_H
