#include "SavesListState.h"
#include <locale>
#include <filesystem>
#include "OneSaveState.h"
#include "MainMenuState.h"

#define QUIT 10

SavesListState::SavesListState(StateData* state_data)
        : State(state_data){
    this->initDeferredRender();
    this->readSavegames();
    this->initFonts();
    this->initGui();
    this->resetGui();
}

SavesListState::~SavesListState()
{
    for (auto &it : this->buttons)
        delete it.second;

    for(auto it : simpleSaves)
        delete it;

    for(auto it : texts)
        delete it;

    delete newGameButton;
    delete quitButton;
}

void SavesListState::readSavegames(){
    try {
        for (const auto& entry : std::filesystem::directory_iterator(this->stateData->localpath+"Config/SaveGames")) {
            auto* temp = new SaveGameBase();
            if(entry.path().extension() == ".ini"){
                temp->loadSimpleFromFile(this->stateData->localpath+"Config/SaveGames/"+entry.path().filename().string());
                temp->path = this->stateData->localpath+"Config/SaveGames/"+entry.path().filename().string();
                simpleSaves.push_back(temp);
            }
        }
    } catch (const std::filesystem::filesystem_error& err) {
        std::cerr << "Filesystem error: " << err.what() << '\n';
    } catch (const std::exception& ex) {
        std::cerr << "General error: " << ex.what() << '\n';
    }
};


void SavesListState::initGui()
{
    const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
    this->background.setSize(sf::Vector2f(static_cast<float>(vm.width),static_cast<float>(vm.height)));

    if (!this->backgroundTexture.loadFromFile(this->stateData->localpath+"Images/LS.png"))
    {
        throw "ERROR::SAVES_LIST_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
    }
    this->background.setTexture(&this->backgroundTexture);


    this->fade.setSize(sf::Vector2f(static_cast<float>(vm.width),static_cast<float>(vm.height)));
    this->fade.setFillColor(sf::Color(20,20,20,255));

    this->title.setPosition(sf::Vector2f(static_cast<float>(gui::calcX(15.f,vm)),static_cast<float>(gui::calcY(9.f,vm))));
    this->title.setString("Zapisy:");
    this->title.setFont(this->font);
    this->title.setStyle(1);
    this->title.setCharacterSize(gui::calcCharSize(vm,30));
    this->title.setFillColor(sf::Color(50,50,50,255));

    auto* ButtonPlayInitParams = new gui::ButtonParams;
    ButtonPlayInitParams->x =  gui::calcX(30,vm);
    ButtonPlayInitParams->width = static_cast<float>(gui::calcCharSize(vm,50)*3);
    ButtonPlayInitParams->height = static_cast<float>(gui::calcCharSize(vm,50)*1);
    ButtonPlayInitParams->font = &this->font;
    ButtonPlayInitParams->character_size = gui::calcCharSize(vm,50);

    int i=0;
    for (;i<simpleSaves.size();i++)
    {
        if (!simpleSaves.empty())
        {
            texts.push_back(gui::CreateText(
                    L"(Punkty: " + std::to_wstring(simpleSaves[i]->getPoints()) + L")",
                    static_cast<float>(gui::calcX(55.f, vm)),
                    static_cast<float>(gui::calcY(22.f + i * 7, vm) + gui::calcCharSize(vm, 110)),
                    &this->font,
                    sf::Color(70, 70, 70, 255),
                    gui::calcCharSize(vm, 90))
                    );

            texts.push_back(gui::CreateText(
                    simpleSaves[i]->getDate(),
                    static_cast<float>(gui::calcX(41.f, vm)),
                    static_cast<float>(gui::calcY(22.f + i * 7, vm) + gui::calcCharSize(vm, 110)),
                    &this->font,
                    sf::Color(70, 70, 70, 255),
                    gui::calcCharSize(vm, 90)
            ));

        ButtonPlayInitParams->text = simpleSaves[i]->getSaveName();
        ButtonPlayInitParams->y = static_cast<float>(gui::calcY(22.f + i * 7, vm));
        this->buttons[i] = new gui::Button(ButtonPlayInitParams);
        }
    }
    ButtonPlayInitParams->text = "Nowa gra";
    ButtonPlayInitParams->y = static_cast<float>(gui::calcY(23.f+(i+1)*7,vm));
    this->newGameButton = new gui::Button(ButtonPlayInitParams);
    if((simpleSaves.empty() ||simpleSaves.size()<8) ){
        this->newGameButton->SetEnabled(true);
    }else{
        this->newGameButton->SetEnabled(false);
    }
    delete ButtonPlayInitParams;


    //Exit
    auto* ButtonInitParams = new gui::ButtonParams;
    ButtonInitParams->x =  gui::calcX(10.f, vm);
    ButtonInitParams->y =  gui::calcY(81.5f, vm);
    ButtonInitParams->width = static_cast<float>(gui::calcCharSize(vm,50)*3);
    ButtonInitParams->height = static_cast<float>(gui::calcCharSize(vm,50)*1.2);
    ButtonInitParams->font = &this->font;
    ButtonInitParams->character_size = gui::calcCharSize(vm);
    ButtonInitParams->text = L"Wróć";

    this->quitButton = new gui::Button(ButtonInitParams);
    delete ButtonInitParams;
}


void SavesListState::resetGui()
{
    for (auto &it : this->buttons)
        delete it.second;

    this->buttons.clear();
    this->initGui();
}


void SavesListState::updateButtons(const float& dt)
{
    this->quitButton->update(this->mousePosWindow,dt);
    if (this->quitButton->isPressed())
        stateptr = new MainMenuState(this->stateData);

    if(newGameButton!= nullptr)
        this->newGameButton->update(this->mousePosWindow,dt);

    if (this->newGameButton!= nullptr && this->newGameButton->isPressed())
    {
        auto* temp = new SaveGame(this->stateData->localpath+"Config/SaveGames/");
        stateptr = new OneSaveState(this->stateData, temp);
    }

    for (auto &it : this->buttons)
        it.second->update(this->mousePosWindow,dt);


    for(auto &el : buttons)
    {
        if (el.second->isPressed())
        {
            auto * temp = new SaveGame();
            temp->path = simpleSaves[el.first]->path;
            temp->loadAllFromFile(simpleSaves[el.first]->path);
            stateptr = new OneSaveState(this->stateData, temp);
        }
    }
}


void SavesListState::update(const float& dt)
{
    this->FadeUpdate(dt);
    this->updateMousePositions();
    if(static_cast<float>(this->stateData->gfxSettings->resolution.width) != background.getSize().x ||
       static_cast<float>(this->stateData->gfxSettings->resolution.height) != background.getSize().y)
    {
        resetGui();
    }
    this->updateButtons(dt);
}


void SavesListState::render(sf::RenderTarget* target)
{
    if (!target)target = this->window;
    this->renderTexture.clear();
    this->renderTexture.draw(this->background);
    this->renderTexture.draw(this->title);
    this->quitButton->render(this->renderTexture);
    this->newGameButton->render(this->renderTexture);

    for (auto &it : this->buttons)
        it.second->render(this->renderTexture);

    for (auto &it : this->texts)
        this->renderTexture.draw(*it);

    this->renderTexture.draw(fade);

    this->renderTexture.display();
    this->renderSprite.setTexture(this->renderTexture.getTexture());
    target->draw(renderSprite);
}



