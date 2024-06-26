/**
 * @file OneSaveState.h
 * @brief One savegame view class
 */
#ifndef HANGMAN_ONESAVESTATE_H
#define HANGMAN_ONESAVESTATE_H

#include "State.h"
#include "../Modules/Gui.h"
#include "../Modules/SaveGame.h"


/**
 * @class OneSaveState
 * @brief One Save State class reponsible for view and logic
 */
class OneSaveState : public State{

private:
    sf::Texture titleTexture; ///<Texture holding title image
    sf::Text title; ///<Title image rectangle to render on the view
    std::map<uint8_t, gui::Button*> buttons; ///<A map that stores the buttons
    std::vector<sf::Text*> texts; ///<All text pointers vector
    SaveGame * saveGamePtr; ///<Pointer to this savegame object

    void createStatTexts();

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
    * @param saveGame Pointer to the savegame object.
    */
    explicit OneSaveState(StateData* state_data, SaveGame * saveGame);

    /**
    * @brief Class destructor
    */
    ~OneSaveState() override;

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

#endif
