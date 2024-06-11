/**
 * @file LoadingState.h
 * @brief Loading view
 */

#ifndef HANGMAN_SETTINGSSTATE_H
#define HANGMAN_SETTINGSSTATE_H
#include "State.h"
#include "../Modules/Gui.h"


/**
 * @class LoadingState
 * @brief Class reponsible for settings view
 */
class LoadingState : public State {

private:
        sf::Texture backgroundTexture; ///<Background texture reference.
        sf::Texture titleTexture; ///<Background texture reference.
        sf::RectangleShape background; ///<Background rectangle object
        sf::Font font;///<Font reference requiered to render text.
        sf::Clock time; ///<Fade in/out clock
        sf::RectangleShape fade;///<Fade in/out black rectangle
        bool fadein=true; ///<Is fading in or out
        sf::Text title; ///<Title text
        /**
        * @brief Reading font from file
        */
        void initFonts();

        /**
        * @brief Function that initialize gui.
        */
        void initGui();
public:
        /**
        * @brief Class constructor
        * @param state_date Pointer to main state data.
        */
        LoadingState(StateData* state_data);

        /**
        * @brief Class destructor
        */
        virtual ~LoadingState();


        /**
        * @brief Basic game loop handling events
        * @param dt Delta time
        */
        void update(const float& dt);

        /**
        * @brief Loop for rendering
        * @param target Pointer to the renderer
        */
        void render(sf::RenderTarget* target = NULL);
};


#endif //HANGMAN_SETTINGSSTATE_H
