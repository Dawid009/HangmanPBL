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

/**
 * @class StateData
 * @brief A class that stores data about state
 */
class StateData
{
public:
    /**
    * @brief Class constructor
    */
    StateData() {};
    sf::RenderWindow* window;///<The game window pointer
    GraphicsSettings* gfxSettings;///<An object that stores settings
    std::stack<State*>* states;///<A stack that stores the views
    std::string localpath;///<Apple bundle path
};

/**
 * @class State
 * @brief Base abstract class to create state based on.
 */
class State {
protected:
    StateData* stateData; ///<Variable holding state data
    std::stack<State*>* states;///<A stack that stores the views
    sf::RenderWindow* window;///<The game window pointer
    sf::Texture backgroundTexture;///<background texture ref
    sf::RenderTexture renderTexture;///<deferred renderer screen view
    sf::Sprite renderSprite; ///<deferred renderer sprite
    sf::RectangleShape background;///<Background rectangle
    bool quit;///<Is the game to be closed
    bool paused;///<Is the game paused
    sf::Vector2i mousePosWindow;///<XY mouse position on the window
    sf::Clock fadeTime; ///<Fade clock object
    sf::RectangleShape fade;///<Fade in/out black rectangle
    bool fadein=true; ///<Is fading in or out
    bool pushedNew=false; ///<Is new state pushed?
    State* stateptr;///<Pointer to new state
    sf::Font font; ///<Font object

    virtual void FadeUpdate(const float& dt);
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
    * @brief Function initializing fonts required to display text.
    */
    void initFonts();

    /**
    * @brief Creates deferred renderer
    */
    void initDeferredRender();

    /**
    * @brief Checks if the game should be terminated
    * @return Returns true or false result
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


#endif