/**
 * @file SettingsState.h
 * @brief Settings view
 */

#ifndef HANGMAN_SETTINGSSTATE_H
#define HANGMAN_SETTINGSSTATE_H

#include "State.h"
#include "../Modules/Gui.h"

/**
 * @class SettingsState
 * @brief Class reponsible for settings view
 */
class SettingsState : public State {
private:
        sf::Texture backgroundTexture; ///<Background texture reference
        sf::RectangleShape background; ///<Background rectangle object
        std::map<std::string, gui::Button*> buttons;///<A map that stores buttons
        std::map<std::string, gui::DropDownList*> dropDownLists;///<A map that stores all dropdown lists
        sf::Text* fpsText; ///<Fps text
        float delay; ///<Fps delay counter
        std::vector<sf::VideoMode> modes; ///<Screen modes read from file
        uint8_t fps[6] = {0,240,120,60,30,15}; ///<Screen fps limits

        /**
        * @brief Function to assign basic values to variables.
        */
        void initVariables();

        /**
        * @brief Function that initialize gui.
        */
        void initGui();

        /**
        * @brief Function to reset Gui to the default state.
        */
        void resetGui();

public:
        /**
        * @brief Class constructor
        * @param state_date Pointer to main state data.
        */
        explicit SettingsState(StateData* state_data);

        /**
        * @brief Class destructor
        */
        ~SettingsState() override;

        /**
        * @brief Basic game loop handling events.
        * @param dt Delta time
        */
        void updateGui(const float& dt);

        /**
        * @brief Basic game loop handling events.
        * @param dt Delta time
        */
        void update(const float& dt) override;

        /**
        * @brief Loop for rendering.
        * @param target Pointer to the renderer
        */
        void render(sf::RenderTarget* target = NULL) override;
};

#endif
