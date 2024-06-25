/**
 * @file SavesListState.h
 * @brief View of all savegames
 */
#ifndef HANGMAN_SAVELISTSTATE_H
#define HANGMAN_SAVELISTSTATE_H

#include "State.h"
#include "../Modules/Gui.h"
#include "../Modules/SaveGame.h"


/**
 * @class SavesListState
 * @brief View of all savegames
 */
class SavesListState : public State{

private:
    sf::Texture titleTexture; ///<Texture holding title image
    sf::Text title; ///<Title image rectangle to render on the view
    sf::Font font; ///<Font reference requiered to display text
    std::map<uint8_t, gui::Button*> buttons; ///<A map that stores the buttons
    gui::Button* quitButton; ///<Quit button pointer
    gui::Button* newGameButton;///<New game button pointer
    std::vector<SaveGameBase*> simpleSaves; ///<All saves in dir
    std::vector<sf::Text*> texts; ///<All text pointers vector

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

    /**
    * @brief Function reading savegames
    */
    void readSavegames();

public:
    /**
    * @brief Class constructor
    * @param state_date Pointer to main state data.
    */
    explicit SavesListState(StateData* state_data);

    /**
    * @brief Class destructor
    */
    virtual ~SavesListState();

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
