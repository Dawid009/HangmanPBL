#include "GameState.h"
#include <locale>
#include <fstream>

GameState::GameState(StateData* state_data)
        : State(state_data)
{
    this->paused = false;
    this->initDeferredRender();
    this->initView();
    this->initFonts();
    this->initPauseMenu();
    this->keyboard = new Keyboard(this->font,this->stateData->gfxSettings);

    std::srand(std::time(nullptr));
    int randomLine = std::rand() % 170;
    std::wstring line;
    int currentLine = 0;

    std::wifstream file(this->stateData->localpath+"Passwords/PL.ini");
    if (file.is_open()) {
        // Iteracyjne odczytywanie pliku
        while (std::getline(file, line)) {
            if (currentLine == randomLine) {
                break;
            }
            currentLine++;
        }
        file.close();
    }else{
        std::cerr << "Nie można otworzyć pliku" << std::endl;
    }



    this->letterFields = new LetterFields(this->font,this->stateData->gfxSettings,line);
    this->hangman = new Hangman(this->stateData->gfxSettings);
    this->pointsModule = new Points(line.length());
}

GameState::~GameState() = default;

void GameState::initDeferredRender()
{
    this->renderTexture.create(
            this->stateData->gfxSettings->resolution.width,
            this->stateData->gfxSettings->resolution.height
    );

    this->renderSprite.setTexture(this->renderTexture.getTexture());
    this->renderSprite.setTextureRect(
            sf::IntRect(
                    0,
                    0,
                    this->stateData->gfxSettings->resolution.width,
                    this->stateData->gfxSettings->resolution.height
            )
    );
}



void GameState::initFonts()
{
    if (!this->font.loadFromFile(this->stateData->localpath+"Fonts/Caveat.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
    }
    std::locale::global(std::locale("pl_PL.UTF-8"));
}


void GameState::initView()
{
    const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

    if(stateData->gfxSettings->showFps){
        fpsText = new sf::Text();
        fpsText->setString("");
        fpsText->setFont(this->font);
        fpsText->setCharacterSize(gui::calcCharSize(vm,70.f));
        fpsText->setPosition(sf::Vector2f(gui::calcX(0.5f,vm),gui::calcY(0.5f,vm)));
        fpsText->setFillColor(sf::Color(20, 20, 20, 255));
    }

    pointsText = new sf::Text();
    pointsText->setString("Punkty");
    pointsText->setFont(this->font);
    pointsText->setCharacterSize(gui::calcCharSize(vm,50.f));
    pointsText->setPosition(sf::Vector2f(gui::calcX(10.f,vm),gui::calcY(2.f,vm)));
    pointsText->setFillColor(sf::Color(20, 20, 20, 255));
    pointsText->setStyle(0);



    this->background.setSize(sf::Vector2f(static_cast<float>(vm.width),static_cast<float>(vm.height)));

    if (!this->backgroundTexture.loadFromFile(this->stateData->localpath+"Images/gamebackground.jpg"))
    {
        throw "ERROR::MAIN_MENU::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
    }

    this->background.setTexture(&this->backgroundTexture);
}


void GameState::initPauseMenu()
{
    const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
    this->pmenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);
    this->pmenu->addButton("QUIT", gui::calcY(74.f, vm), gui::calcX(13.f, vm), gui::calcY(6.f, vm), gui::calcCharSize(vm), L"Wyjdz");
    this->pmenu->addButton("RESTART", gui::calcY(45.f, vm), gui::calcX(13.f, vm), gui::calcY(6.f, vm), gui::calcCharSize(vm), L"Restart");
    this->pmenu->addButton("CONTINUE", gui::calcY(35.f, vm), gui::calcX(13.f, vm), gui::calcY(6.f, vm), gui::calcCharSize(vm), L"Kontynuuj");
}


void GameState::checkKeyboard(const uint8_t letter) {
    if(misses<6){
        if(this->keyboard->IsPressed(letter)){
            if(auto points = this->letterFields->revealLetter(letter)){
                this->pointsModule->addPoints(letter, points);
                this->keyboard->SetButtonEnabled(letter,false);
                this->keyboard->SetButtonColor(letter,sf::Color(0,153,0,255));
            }else{
                this->pointsModule->addPoints(letter, points);
                this->keyboard->SetButtonEnabled(letter,false);
                this->keyboard->SetButtonColor(letter,sf::Color(250,0,0,255));
                misses++;
                this->hangman->setLevel(misses);
            };

        }
    }else{
        this->keyboard->SetButtonEnabled(letter,false);
        this->letterFields->revealLetter(letter);
    }
    pointsText->setString("Punkty: "+std::to_string(this->pointsModule->getPoints()));
}


void GameState::updatePauseMenuButtons()
{
    if (this->pmenu->isButtonPressed("QUIT"))
        this->endState();
    if (this->pmenu->isButtonPressed("CONTINUE"))
        this->paused = false;
    if (this->pmenu->isButtonPressed("RESTART")) {
        this->states->pop();
        this->states->push(new GameState(stateData));
    }
}


void GameState::update(const float& dt)
{
    this->updateMousePositions(&this->view);

    if (!this->paused) //gra w  trakcie
    {
        this->keyboard->update(mousePosWindow,dt);
        this->letterFields->update(dt);

        //Sprawdzanie czy nacisniety przycisk
        for(uint8_t i{0};i<34;i++){
            checkKeyboard(i);
        }

        if(this->keyboard->IsPressed(L'*')){
            this->paused = true;
        }

    }
    else //gra zapauzowana
    {
        this->pmenu->update(this->mousePosWindow,dt);
        this->updatePauseMenuButtons();
    }


    if(this->stateData->gfxSettings->showFps && delay>1.5f){
        fpsText->setString(std::to_string(static_cast<int>(1/dt)));
        delay=0;
    }else{
        delay+=dt;
    }
}


void GameState::render(sf::RenderTarget* target)
{
    //dodać prerenderowanie niektórych elementów
    this->renderTexture.clear();
    if (!target)
        target = this->window;
    this->renderTexture.clear();
    //target->draw(this->background);

    renderTexture.draw(this->background);
    this->hangman->render(&renderTexture);
    this->keyboard->render(&renderTexture);
    this->letterFields->render(&renderTexture);

    if(this->stateData->gfxSettings->showFps){
        renderTexture.draw(*fpsText);
    }

    renderTexture.draw(*pointsText);

    if (this->paused)
    {
        this->pmenu->render(this->renderTexture);
    }

    this->renderTexture.display();
    this->renderSprite.setTexture(this->renderTexture.getTexture());
    target->draw(renderSprite);
}

