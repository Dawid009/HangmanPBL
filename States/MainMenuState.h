/**
 * @file MainMenuState.h
 * @brief Main menu view class
 */
#ifndef HANGMAN_MAINMENUSTATE_H
#define HANGMAN_MAINMENUSTATE_H

#include "State.h"
#include "../Modules/Gui.h"
#include "GameState.h"

/**
 * @class MainMenuState
 * @brief Main Menu class reponsible for view and logic
 */
class MainMenuState : public State{

private:
    sf::Texture titleTexture; ///<Texture holding title image
    sf::Text title; ///<Title image rectangle to render on the view
    sf::Font font; ///<Font reference requiered to display text
    std::map<uint8_t, gui::Button*> buttons; ///<A map that stores the buttons
    sf::Clock time; ///<Fade in/out clock
    sf::RectangleShape fade;///<Fade in/out black rectangle
    bool fadein=true; ///<Is fading in or out
    bool pushedNew=false;///<Is new state pushed?
    State* stateptr;///<Pointer to new state
    /**
    * @brief Function initializing fonts required to display text.
    */
    void initFonts();

    /**
    * @brief Function initializing main manu gui.
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
    explicit MainMenuState(StateData* state_data);

    /**
    * @brief Class destructor
    */
    virtual ~MainMenuState();

    /**
    * @brief Function about buttons work. Updating buttons events
    * @param dt Delta time value
    */
    void updateButtons(const float& dt);

    /**
    * @brief Main state loop updating events
    * @param dt Delta time value
    */
    void update(const float& dt) override;

     /**
     * @brief Loop for rendering
     * @param target Pointer to the renderer
     */
    void render(sf::RenderTarget* target = nullptr) override;
};

#endif //HANGMAN_MAINMENUSTATE_H
