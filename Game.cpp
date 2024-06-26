#include "Game.h"

#include <CoreFoundation/CoreFoundation.h>

Game::Game()
{
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    if (mainBundle) {
        CFURLRef bundleURL = CFBundleCopyBundleURL(mainBundle);
        if (bundleURL) {
            CFStringRef bundlePath = CFURLCopyFileSystemPath(bundleURL, kCFURLPOSIXPathStyle);
            if (bundlePath) {
                char path[PATH_MAX];
                if (CFStringGetCString(bundlePath, path, sizeof(path), kCFStringEncodingUTF8)) {
                    std::string bundlePathString(path);
                    std::cout << "Bundle path: " << bundlePathString << std::endl;
                    this->stateData.localpath = bundlePathString+"/Contents/Resources/";
                }
                CFRelease(bundlePath);
            }
            CFRelease(bundleURL);
        }
    }
    this->initVariables();
    this->initGraphicsSettings();
    this->initWindow();
    this->initStateData();
    this->initStates();
}

Game::~Game()
{
    delete this->window;

    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}


void Game::initVariables()
{
    this->window = nullptr;
    this->dt = 0.f;
}


void Game::initWindow()
{
    this->window = new sf::RenderWindow(
            this->gfxSettings.resolution,
            this->gfxSettings.title,
            this->gfxSettings.fullscreen ? sf::Style::Fullscreen : sf::Style::Titlebar | sf::Style::Close,
            this->gfxSettings.contextSettings);

    this->window->setFramerateLimit(this->gfxSettings.frameRateLimit);
    this->window->setVerticalSyncEnabled(this->gfxSettings.verticalSync);
}

void Game::updateDt()
{
    this->dt = this->dtClock.restart().asSeconds();
}


void Game::initGraphicsSettings()
{
    this->gfxSettings.loadFromFile(this->stateData.localpath+"Config/graphics.ini");
}


void Game::initStateData()
{
    this->stateData.gfxSettings = &this->gfxSettings;
    this->stateData.window = this->window;
    this->stateData.states = &this->states;
}


void Game::initStates()
{
    this->states.push(new LoadingState(&this->stateData));
}


void Game::update()
{
    //SFML EVENTS
    while (this->window->pollEvent(this->sfEvent))
    {
        if (this->sfEvent.type == sf::Event::Closed)
            this->window->close();
    }

    if (!this->states.empty())
    {
        if (this->window->hasFocus())
        {
            this->states.top()->update(this->dt);

            if (this->states.top()->getQuit())
            {
                this->states.top()->endState();
                delete this->states.top();
                this->states.pop();
            }
        }
    }
    else
    {
        this->window->close();
    }
}


void Game::render()
{
    this->window->clear();
    if (!this->states.empty()){
        this->states.top()->render();
    }
    this->window->display();
}


void Game::run()
{
    while (this->window->isOpen())
    {
        this->updateDt();
        this->update();
        this->render();
    }
}