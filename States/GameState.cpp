#include "GameState.h"
#include <locale>
#include <fstream>
#include <algorithm>
#include "OneSaveState.h"

GameState::GameState(StateData* state_data, SaveGame* saveGame)
        : State(state_data), saveGamePtr(saveGame), misses(0)
{
    this->paused = false;
    this->initDeferredRender();
    this->initView();
    this->initFonts();
    this->initPauseMenu();
    this->keyboard = new Keyboard(this->font,this->stateData->gfxSettings);

    std::wstring line;
    this->pickRandomPassword(line,170);

    this->letterFields = new LetterFields(this->font,this->stateData->gfxSettings,line);
    this->hangman = new Hangman(this->stateData->gfxSettings);
    this->pointsModule = new Points(line.length());
}

GameState::~GameState() {
    delete letterFields;
    delete hangman;
    delete keyboard;
    if(fpsText!= nullptr) delete fpsText;
    delete pointsText;
    delete pmenu;
    delete pointsModule;
    std::cout<<"Destruktor gamestate!"<<std::endl;
}


void GameState::pickRandomPassword(std::wstring& stringRef,int maxRow){
    if(saveGamePtr->current_password_id!=0)
        passwordLine=saveGamePtr->current_password_id;
    else {
        std::srand(std::time(nullptr));
        passwordLine = (std::rand() % maxRow) + 1;
    }
    std::wstring line;
    int currentLine = 1;

    std::wifstream file(this->stateData->localpath+"Keywords/PL.ini");
    if (file.is_open()) {
        while (std::getline(file, line)) {
            if (currentLine == passwordLine) {
                break;
            }
            currentLine++;
        }
        file.close();
    }else{
        std::cerr << "Nie można otworzyć pliku" << std::endl;
    }

    saveGamePtr->current_password_id=passwordLine;
    stringRef = line;
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
    this->pmenu->addButton("QUIT", gui::calcY(74.f, vm), gui::calcX(13.f, vm), gui::calcY(6.f, vm), gui::calcCharSize(vm), L"Wyjdź");
    this->pmenu->addButton("CONTINUE", gui::calcY(35.f, vm), gui::calcX(13.f, vm), gui::calcY(6.f, vm), gui::calcCharSize(vm), L"Kontynuuj");
    this->endScreen = new EndScreen(this->stateData->gfxSettings->resolution,this->font);
}


void GameState::checkKeyboard(const uint8_t letter) {

    if(timeClock.getElapsedTime().asSeconds()>1 && !ended){
        timeClock.restart();
        this->saveGamePtr->playtime+=totalTime;
        totalTime=0;
    }
    if(misses<6){
        if(this->keyboard->IsPressed(letter)){
            if(auto points = this->letterFields->revealLetter(letter)){
                passes+=points;
                this->saveGamePtr->total_good_hits++;
                this->pointsModule->addPoints(letter, points);
                this->keyboard->SetButtonEnabled(letter,false);
                this->keyboard->SetButtonColor(letter,sf::Color(0,153,0,255));
            }else{
                this->saveGamePtr->total_miss_hits++;
                this->pointsModule->addPoints(letter, points);
                this->keyboard->SetButtonEnabled(letter,false);
                this->keyboard->SetButtonColor(letter,sf::Color(250,0,0,255));
                misses++;
                this->hangman->setLevel(misses);
            };
            this->saveGamePtr->picked_letters.push_back(letter);
            this->saveGamePtr->date = Date();

            this->saveGamePtr->saveToFile(saveGamePtr->path);
        }

        if(!initRevealed) {
            for (auto letter: saveGamePtr->picked_letters) {
                if (auto points = this->letterFields->revealLetter(letter)) {
                    passes+=points;
                    this->pointsModule->addPoints(letter, points);
                    this->keyboard->SetButtonEnabled(letter, false);
                    this->keyboard->SetButtonColor(letter, sf::Color(0, 153, 0, 255));
                } else {
                    this->pointsModule->addPoints(letter, points);
                    this->keyboard->SetButtonEnabled(letter, false);
                    this->keyboard->SetButtonColor(letter, sf::Color(250, 0, 0, 255));
                    misses++;
                    this->hangman->setLevel(misses);
                };
            }
            initRevealed = true;
        }
        endClock.restart();
    }else{
        for(int i=0;i<34;i++)
            letterFields->revealLetter(i);

        if(!ended){
            if (endClock.getElapsedTime().asSeconds() >= 2) {
                this->keyboard->SetButtonEnabled(letter,false);
                this->letterFields->revealLetter(letter);
                this->saveGamePtr->addPoints(this->pointsModule->getPoints()*-1);
                this->saveGamePtr->current_password_id=0;
                this->saveGamePtr->picked_letters.clear();
                this->saveGamePtr->loss_games++;
                this->saveGamePtr->saveToFile(this->saveGamePtr->path);
                this->endScreen->setWin(false);
                ended =true;
            }
        }
    }

    if(this->letterFields->getLength()==passes){
        if(ended==false) {
            if (endClock.getElapsedTime().asSeconds() >= 2) {
                this->saveGamePtr->addPoints(this->pointsModule->getPoints());
                this->saveGamePtr->win_games_id.push_back(this->saveGamePtr->current_password_id);
                this->saveGamePtr->current_password_id = 0;
                this->saveGamePtr->picked_letters.clear();
                this->saveGamePtr->win_games++;
                this->saveGamePtr->saveToFile(this->saveGamePtr->path);
                this->endScreen->setWin(true);
                ended = true;
            }
        }
    }
    pointsText->setString("Punkty: "+std::to_string(this->pointsModule->getPoints()));
}


void GameState::updatePauseMenuButtons() {
    if (this->pmenu->isButtonPressed("QUIT")) {
        OneSaveState *temp = new OneSaveState(this->stateData, saveGamePtr);
        this->endState();
        this->states->pop();
        this->states->push(temp);
    }
    if (this->pmenu->isButtonPressed("CONTINUE"))
        this->paused = false;
}


void GameState::updateEndScreenButtons() {
    if(this->endScreen->isButtonPressed("NEW")){
        auto * temp = new GameState(this->stateData, saveGamePtr);
        this->states->pop();
        this->states->push(temp);
        this->endState();
    }

    if(this->endScreen->isButtonPressed("QUIT")){
        auto * temp = new OneSaveState(this->stateData, saveGamePtr);
        this->states->pop();
        this->states->push(temp);
        this->endState();
    }


}

void GameState::update(const float& dt)
{
    this->updateMousePositions(&this->view);

    if (!this->paused && !ended)
    {
        totalTime+=dt;
        this->letterFields->update(dt);
        this->keyboard->update(mousePosWindow,dt);

        for(uint8_t i{0};i<34 && !ended;i++){
            checkKeyboard(i);
        }

        if(this->keyboard->IsPressed(L'*')){
            this->paused = true;
        }
    }
    else
    {
        timeClock.restart();
        this->pmenu->update(this->mousePosWindow,dt);
        this->updatePauseMenuButtons();
    }

    if(this->ended) {
        timeClock.restart();
        this->updateEndScreenButtons();
        this->endScreen->update(this->mousePosWindow, dt);
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
    if (!target) target = this->window;
    this->renderTexture.clear();
    renderTexture.draw(this->background);
    renderTexture.draw(*pointsText);

    this->hangman->render(&renderTexture);
    this->keyboard->render(&renderTexture);
    this->letterFields->render(&renderTexture);

    if(this->stateData->gfxSettings->showFps)
        renderTexture.draw(*fpsText);

    if (this->paused && !ended)
        this->pmenu->render(this->renderTexture);

    if(this->ended)
        this->endScreen->render(this->renderTexture);

    this->renderTexture.display();
    this->renderSprite.setTexture(this->renderTexture.getTexture());
    target->draw(renderSprite);
}