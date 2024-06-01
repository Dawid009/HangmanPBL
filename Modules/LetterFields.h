/**
 * @file LetterFields.h
 * @brief A file containing a class with the same name
 */
#ifndef HANGMAN_LETTERFIELDS_H
#define HANGMAN_LETTERFIELDS_H
#include "Gui.h"
#include <vector>
/**
 * @brief Structure representing one field displayed on the screen
 */
struct LetterField{
    uint8_t id; ///<Id for textfield identification
    sf::RectangleShape* floor; ///<Pointer to the floor of the field
    sf::Text* text; ///<Text to be displayed on the screen
    float targetAlpha=0; ///<Target alpha used in linear interpolation

    /**
    * @brief Struct constructor
    * @param id Id of the field
    * @param floor Pointer to the floor object
    * @param text Text to be displayed on the screen
    */
    LetterField(uint8_t id, sf::RectangleShape* floor, sf::Text* text):
        id(id),
        floor(floor),
        text(text)
        {}
};

/**
 * @class LetterFields
 * @brief Class reponsible for drawing and revealing letters on the screen.
 */
class LetterFields {
private:
    std::vector<LetterField*> Fields;///<A vector that stores all letter
    class GraphicsSettings* gfxSettings;///<Pointer to the graphics settings
    sf::Font font;///<Font reference requiered to render text.

    /**
    * @brief Function creating all fields and their views.
    * @param password Password to be created visually and stored in array.
    */
    void initLetterFields(const std::wstring& password);

public:
    /**
    * @brief Class constructor
    */
    LetterFields(const sf::Font& font, GraphicsSettings* settings,const std::wstring& password);
    /**
    * @brief Class destructor
    * @param font Font reference
    * @param settings Pointer to global graphics settings
    * @param password Word to be displayed on the screen
    */
    virtual ~LetterFields();

    /**
    * @brief Main module loop updating events
    * @param dt Delta time value
    */
    void update(const float& dt);

    /**
    * @brief Loop for rendering
    * @param target Pointer to the renderer
    */
    void render(sf::RenderTarget* target = nullptr);

    /**
    * @brief Function that checks whether the text contains a given letter and reveals it
    * @param letter Id of the letter to be checked
    * @returns Return amount of points
    */
    int revealLetter(uint8_t letter);
};


#endif //HANGMAN_LETTERFIELDS_H
