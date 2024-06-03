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
     * @brief Class constructor
     * @param a Current value
     * @param b The value to which the function is going
     * @param t Speed modifier
     * @returns Returns the value for a given iteration
     */
    float lerp(float a, float b, float t);
    /**
    * @brief Based on the percentage of the window, calculates the value of X
    * @param percent Percentage of screen from point 0
    * @param vm Pointer to VideoMode
    * @returns Returns the X value
    */
    float calcX(float percent, const sf::VideoMode& vm);
    /**
    * @brief Based on the percentage of the window, calculates the value of Y
    * @param percent Percentage of screen from point 0
    * @param vm Pointer to VideoMode
    * @returns Returns the Y value
    */
    float calcY(float percent, const sf::VideoMode& vm);
    /**
    * @brief Calculates character size on the screen
    * @param vm Pointer to VideoMode
    * @param modifier Char size modifier
    * @returns Returns character size value
    */
    unsigned calcCharSize(const sf::VideoMode& vm, unsigned modifier = 60);

    /**
    * @struct ButtonParams
    * @brief Options when creating a button
    */
    struct ButtonParams {
        float x{20.f}; ///<Button position x
        float y{20.f}; ///<Button position y
        float width{50.f}; ///<Button width
        float height{50.f}; ///<Button height
        sf::Font* font{nullptr}; ///<Pointer to any font
        sf::String text{""}; ///<Text to be displayed on the button
        unsigned character_size{10}; ///<Text character size
        float thickness{3.f}; ///<Button outline thickness
        sf::Color text_idle_color{sf::Color(70,70,70,255)}; ///<Text idle color
        sf::Color text_hover_color{sf::Color(40,40,40,255)};///<Text color when hovered
        sf::Color text_active_color{sf::Color(20,20,20,255)};///<Text color when pressed
        sf::Color outline_idle_color{sf::Color::Transparent}; ///<Outline idle color
        sf::Color outline_hover_color{sf::Color::Transparent};///<Outline color when hovered
        sf::Color outline_active_color{sf::Color::Transparent};///<Outline color when pressed
        sf::Color background_idle_color{sf::Color::Transparent};///<Outline idle color
        sf::Color background_hover_color{sf::Color::Transparent};///<Outline color when hovered
        sf::Color background_active_color{sf::Color::Transparent};///<Outline color when pressed
        float hoverScale{1.2f}; ///<Scale of button when hovered
        float activeScale{1.1f};///<Scale of button when pressed
        float scaleToIdleTime{8.f};///<Scale time required to transit to idle
        float scaleToHoverTime{6.5f};///<Scale time required to transit to hover
        float scaleToActiveTime{10.f};///<Scale time required to transit to idle
        bool drawDebugBorder{false};///<Should draw red button border
        bool initEnable{true};///<Should button be enabled
        short id{0}; ///<Button id
    };

    /**
    * @struct DropDownParams
    * @brief Options when creating a dropdown
    */
    struct DropDownParams{
        float x{20.f}; ///<Dropdown position x
        float y{20.f}; ///<Dropdown position y
        float width{50.f}; ///<Dropdown width
        float height{50.f};///<Dropdown one element height
        sf::Font* font{nullptr};///<Pointer to any font
        unsigned nrOfElements{0}; ///<Element list size
        unsigned character_size{15}; ///<Character size
        short id{0};///<Default index
        std::string* list{nullptr};///<List of elements
        std::string* label{nullptr}; ///<Label above the list
    };

    /**
    * @class Button
    * @brief Class representing a button on the screen
    */
    class Button {
    private:
        short unsigned buttonState;///<Current state of the button
        short unsigned id; ///<Button id

        sf::RectangleShape shape; ///<SFML rectangle
        sf::Text text; ///<Text to be displayed on the button

        sf::Color textIdleColor;  ///<Text idle color
        sf::Color textHoverColor; ///<Text color when hovered
        sf::Color textActiveColor;///<Text color when pressed

        sf::Color outlineIdleColor;///<Outline idle color
        sf::Color outlineHoverColor;///<Outline color when hovered
        sf::Color outlineActiveColor;///<Outline color when pressed

        sf::Color backgroundIdleColor;///<Outline idle color
        sf::Color backgroundHoverColor;///<Outline color when hovered
        sf::Color backgroundActiveColor;///<Outline color when pressed

        float hoverScale;///<Scale of button when hovered
        float activeScale;///<Scale of button when pressed

        float scaleToIdleTime;///<Scale time required to transit to idle
        float scaleToHoverTime;///<Scale time required to transit to hover
        float scaleToActiveTime;///<Scale time required to transit to idle

        bool enabled;///<Should button be enabled

        static bool mousePressed;///<Is left mouse button pressed anywhere

    public:
        /**
        * @brief Class constructor
        * @param params Object with all button settings
        */
        explicit Button(ButtonParams * params);

        /**
        * @brief Class destructor
        */
        ~Button();

        /**
        * @brief Checks if the button is pressed
        * @return Returns a logical yes or no
        */
        bool isPressed() const;

        /**
        * @brief Sets the button to on or off
        * @param enabled Should be enabled?
        */
        void SetEnabled(bool enable);

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

        /**
        * @brief Gets text from the button
        * @return Returns a text
        */
        std::string getText() const;

        /**
        * @brief Gets id of the button
        * @return returns an id
        */
        const short unsigned& getId() const;

        /**
        * @brief Setting button text
        * @param text Text to be set
        */
        void setText(const std::string& text);

        /**
        * @brief Setting button id
        * @param id Id
        */
        void setId(short unsigned id);
    };

    /**
    * @class DropDownList
    * @brief DropDown-list
    */
    class DropDownList
    {
    private:
        float keytime; ///<Keytime
        float keytimeMax;///<KeytimeMax

        sf::Font& font;///<Font reference requiered to render text.
        sf::Text* label;
        gui::Button* activeElement;///<Active dropdown element
        std::vector<gui::Button*> list;///<All dropdown positions
        bool showList;///<Should list be visible
        int renderIndex;
        sf::Clock elapsed;

    public:
        /**
        * @brief Class constructor
        * @param params Object with all dropdown settings
        */
        explicit DropDownList(DropDownParams* params);

        /**
        * @brief Class destructor
        */
        ~DropDownList();

        /**
        * @brief Returns the id of the current selection
        * @return returns Id
        */
        const unsigned short& getActiveElementId() const;

        /**
        * @brief Get keytime value
        * @return returns keytime
        */
        bool getKeytime();

        /**
        * @brief Main module loop updating events
        * @param dt Delta time value
        */
        void update(const sf::Vector2i& mousePosWindow, const float& dt);

        /**
        * @brief Loop for rendering
        * @param target Pointer to the renderer
        */
        void render(sf::RenderTarget& target);
    };


}
#endif //HANGMAN_GUI_H
