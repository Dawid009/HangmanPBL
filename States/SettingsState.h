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
        sf::Texture backgroundTexture; ///<Background texture reference.
        sf::RectangleShape background; ///<Background rectangle object
        sf::Font font;///<Font reference requiered to render text.

        std::map<std::string, gui::Button*> buttons;///<A map that stores buttons
        std::map<std::string, gui::DropDownList*> dropDownLists;///<A map that stores all dropdown lists

        sf::Text optionsText; ///<Options text

        std::vector<sf::VideoMode> modes; ///<Screen modes read from file

        /**
        * @brief Function to assign basic values to variables
        */
        void initVariables();

        /**
        * @brief Reading font from file
        */
        void initFonts();

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
        SettingsState(StateData* state_data);

        /**
        * @brief Class destructor
        */
        virtual ~SettingsState();

        /**
        * @brief Basic game loop handling events
        * @param dt Delta time
        */
        void updateGui(const float& dt);

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
