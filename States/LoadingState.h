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
        sf::Clock time; ///<Fade in/out clock
        sf::RectangleShape fade;///<Fade in/out black rectangle
        bool fadein=true; ///<Is fading in or out
        sf::Text title; ///<Title text

        /**
        * @brief Function that initialize gui.
        */
        void initGui();
        /**
        * @brief Fade update override
        * @param dt Delta time
        */
        void FadeUpdate(const float &dt) override;
public:
        /**
        * @brief Class constructor
        * @param state_date Pointer to main state data.
        */
        explicit LoadingState(StateData* state_data);

        /**
        * @brief Class destructor
        */
        ~LoadingState() override;

        /**
        * @brief Basic game loop handling events
        * @param dt Delta time
        */
        void update(const float& dt) override;

        /**
        * @brief Loop for rendering
        * @param target Pointer to the renderer
        */
        void render(sf::RenderTarget* target = NULL) override;
};


#endif
