#include "SavesListState.h"
#include <locale>
#include <filesystem>
#include "OneSaveState.h"
#include "MainMenuState.h"

#define QUIT 10

SavesListState::SavesListState(StateData* state_data)
        : State(state_data),stateptr(nullptr)
{
    this->readSavegames();
    this->initFonts();
    this->initGui();
    this->resetGui();
}

SavesListState::~SavesListState()
{
    for (auto &it : this->buttons)
    {
        delete it.second;
    }
    delete quitButton;
}

void SavesListState::readSavegames(){
    std::vector<std::string> filenames;

    try {
        for (const auto& entry : std::filesystem::directory_iterator(this->stateData->localpath+"Config/SaveGames")) {
            SaveGameBase* temp = new SaveGameBase();
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

void SavesListState::initFonts()
{
    if (!this->font.loadFromFile(this->stateData->localpath+"Fonts/Caveat.ttf"))
    {
        throw("ERROR: Nie udalo sie zaladowac czcionki");
    }
}


void SavesListState::initGui()
{
    const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
    this->background.setSize(sf::Vector2f(static_cast<float>(vm.width),static_cast<float>(vm.height)));

    if (!this->backgroundTexture.loadFromFile(this->stateData->localpath+"Images/LS.png"))
    {
        throw "ERROR::MAIN_MENU::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
    }


    this->fade.setSize(
            sf::Vector2f
                    (
                            static_cast<float>(vm.width),
                            static_cast<float>(vm.height)
                    )
    );

    this->fade.setFillColor(sf::Color(20,20,20,255));


    this->title.setPosition(sf::Vector2f(static_cast<float>(gui::calcX(15.f,vm)),static_cast<float>(gui::calcY(9.f,vm))));
    this->title.setString("Zapisy:");
    this->title.setFont(this->font);
    this->title.setStyle(1);
    this->title.setCharacterSize(gui::calcCharSize(vm,30));
    this->title.setFillColor(sf::Color(50,50,50,255));

    this->background.setTexture(&this->backgroundTexture);

    auto* ButtonPlayInitParams = new gui::ButtonParams;
    ButtonPlayInitParams->x =  gui::calcX(30,vm);
    ButtonPlayInitParams->width = static_cast<float>(gui::calcCharSize(vm,50)*3);
    ButtonPlayInitParams->height = static_cast<float>(gui::calcCharSize(vm,50)*1);
    ButtonPlayInitParams->font = &this->font;
    ButtonPlayInitParams->character_size = gui::calcCharSize(vm,50);
    ButtonPlayInitParams->hoverScale = 1.2f;
    ButtonPlayInitParams->activeScale = 1.1f;
    ButtonPlayInitParams->text_idle_color= sf::Color(40, 40, 40, 255);
    ButtonPlayInitParams->text_hover_color= sf::Color(25, 25, 25, 255);
    ButtonPlayInitParams->text_active_color= sf::Color(10, 10, 10, 255);

    int i=0;
    for (;i<simpleSaves.size();i++) {
        if (!simpleSaves.empty()){
            sf::Text *temp = new sf::Text(L"(Punkty: " + std::to_wstring(simpleSaves[i]->getPoints()) + L")",
                                          this->font, gui::calcCharSize(vm, 90));
            temp->setPosition(sf::Vector2f(static_cast<float>(gui::calcX(55.f, vm)),
                                       static_cast<float>(gui::calcY(22.f + i * 7, vm) + gui::calcCharSize(vm, 110))));
            temp->setFillColor(sf::Color(70, 70, 70, 255));
            texts.push_back(temp);

            sf::Text *temp2 = new sf::Text(simpleSaves[i]->getDate(),
                                          this->font, gui::calcCharSize(vm, 90));
            temp2->setPosition(sf::Vector2f(static_cast<float>(gui::calcX(41.f, vm)),
                                           static_cast<float>(gui::calcY(22.f + i * 7, vm) + gui::calcCharSize(vm, 110))));
            temp2->setFillColor(sf::Color(70, 70, 70, 255));
            texts.push_back(temp2);

        ButtonPlayInitParams->text = simpleSaves[i]->getSaveName();
        ButtonPlayInitParams->y = static_cast<float>(gui::calcY(22.f + i * 7, vm));
        this->buttons[i] = new gui::Button(ButtonPlayInitParams);
    }


        if((simpleSaves.empty() ||simpleSaves.size()<8) ){
            ButtonPlayInitParams->text = "Nowa gra";
            ButtonPlayInitParams->y = static_cast<float>(gui::calcY(22.f+(i+1)*7,vm));
            this->newGameButton = new gui::Button(ButtonPlayInitParams);
            this->newGameButton->SetEnabled(true);
        }else{
            ButtonPlayInitParams->text = "Nowa gra";
            ButtonPlayInitParams->y = static_cast<float>(gui::calcY(22.f+(i+1)*7,vm));
            this->newGameButton = new gui::Button(ButtonPlayInitParams);
            this->newGameButton->SetEnabled(false);
        }

    }

    if((simpleSaves.empty() ||simpleSaves.size()<8) ){
        ButtonPlayInitParams->text = "Nowa gra";
        ButtonPlayInitParams->y = static_cast<float>(gui::calcY(23.f+(i+1)*7,vm));
        this->newGameButton = new gui::Button(ButtonPlayInitParams);
        this->newGameButton->SetEnabled(true);
    }else{
        ButtonPlayInitParams->text = "Nowa gra";
        ButtonPlayInitParams->y = static_cast<float>(gui::calcY(23.f+(i+1)*7,vm));
        this->newGameButton = new gui::Button(ButtonPlayInitParams);
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
    ButtonInitParams->hoverScale = 1.2f;
    ButtonInitParams->activeScale = 1.1f;
    ButtonInitParams->text_idle_color= sf::Color(40, 40, 40, 255);
    ButtonInitParams->text_hover_color= sf::Color(25, 25, 25, 255);
    ButtonInitParams->text_active_color= sf::Color(10, 10, 10, 255);
    ButtonInitParams->text = L"Wróć";

    this->quitButton = new gui::Button(ButtonInitParams);
    delete ButtonInitParams;
}


void SavesListState::resetGui()
{
    for (auto &it : this->buttons)
    {
        delete it.second;
    }
    this->buttons.clear();
    this->initGui();
}


void SavesListState::updateButtons(const float& dt)
{
    this->quitButton->update(this->mousePosWindow,dt);
    if (this->quitButton->isPressed())
    {
        stateptr = new MainMenuState(this->stateData);
    }
    if(this->newGameButton!= nullptr)
    this->newGameButton->update(this->mousePosWindow,dt);


    if (this->newGameButton!= nullptr && this->newGameButton->isPressed())
    {
        SaveGame * temp = new SaveGame(this->stateData->localpath+"Config/SaveGames/");
        stateptr = new OneSaveState(this->stateData, temp);
    }

    for (auto &it : this->buttons)
    {
        it.second->update(this->mousePosWindow,dt);
    }

    for(auto &el : buttons) {
      if (el.second->isPressed()) {
            SaveGame * temp = new SaveGame();
            temp->path = simpleSaves[el.first]->path;
            temp->loadAllFromFile(simpleSaves[el.first]->path);
            stateptr = new OneSaveState(this->stateData, temp);
        }
    }
}


void SavesListState::update(const float& dt)
{
    if(fadein){
        this->fade.setFillColor(sf::Color(20,20,20,this->fade.getFillColor().a-dt*1000));
        if(this->fade.getFillColor().a<20){
            fadein=false;
        }
        time.restart();
    }

    if (!pushedNew && stateptr!= nullptr) {
        this->fade.setFillColor(sf::Color(20,20,20,this->fade.getFillColor().a+dt*900));
        if(this->fade.getFillColor().a>240){
            pushedNew=true;
            this->states->pop();
            this->stateData->states->push(stateptr);
        }
    }


    this->updateMousePositions();
    if(this->stateData->gfxSettings->resolution.width != background.getSize().x || this->stateData->gfxSettings->resolution.height != background.getSize().y){
        resetGui();
    }
    this->updateButtons(dt);
}


void SavesListState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    target->draw(this->background);
    target->draw(this->title);

    this->quitButton->render(*target);
    if(this->newGameButton!= nullptr)
    this->newGameButton->render(*target);
    //Renderowanie buttonów
    for (auto &it : this->buttons)
    {
        it.second->render(*target);
    }

    for (auto &it : this->texts)
    {
        target->draw(*it);
    }

    target->draw(fade);
}


