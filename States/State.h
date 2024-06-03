/**
 * @file State.h
 * @brief Base State file
 */
#ifndef HANGMAN_STATE_H
#define HANGMAN_STATE_H

#include <SFML/Graphics.hpp>
#include <stack>
#include "../Modules/GraphicsSettings.h"
class State;

/** @class StateData
 * @brief A class that stores data about state
 * */
class StateData
{
public:
    /**
    * @brief Class constructor
    */
    StateData() {};
    sf::RenderWindow* window;///<The game window pointer.
    GraphicsSettings* gfxSettings;///<An object that stores settings
    std::stack<State*>* states;///<A stack that stores the views.
    std::string localpath;
};

/**
 * @class State
 * @brief Base abstract class to create state based on.
 */
class State {
protected:
    StateData* stateData; ///<Variable holding state data
    std::stack<State*>* states;///<A stack that stores the views.
    sf::RenderWindow* window;///<The game window pointer.
    sf::Texture backgroundTexture;///<background texture ref.
    sf::RectangleShape background;///<Background rectangle.
    bool quit;///<Is the game to be closed
    bool paused;///<Is the game paused
    sf::Vector2i mousePosWindow;///<XY mouse position on the window

public:
    /**
    * @brief Class constructor
    * @param state_data  Pointer to main StateData
    */
    State(StateData* state_data);

    /**
    * @brief Class destructor
    */
    virtual ~State();

    /**
    * @brief Function to terminate the state
    */
    void endState();

    /**
    * @brief Checks if the game should be terminated
    * @return Returns the result
    */
    const bool& getQuit() const;

    /**
    * @brief Function that updates the mouse position.
    * @param view Pointer to the view component
    */
    virtual void updateMousePositions(sf::View* view = nullptr);

    /**
    * @brief Loop for events
    * @param dt Delta time
    */
    virtual void update(const float& dt) = 0;

    /**
    * @brief Loop for rendering
    * @param target Pointer to the main renderer
    */
    virtual void render(sf::RenderTarget* target = nullptr) = 0;
};


#endif //HANGMAN_STATE_H
