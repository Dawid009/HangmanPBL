#include "OneSaveState.h"
#include <locale>
#include "GameState.h"

#define QUIT 10
#define PLAY 11

OneSaveState::OneSaveState(StateData* state_data, SaveGame * saveGame)
        : State(state_data), saveGamePtr(saveGame)
{
    this->initFonts();
    this->initGui();
    this->resetGui();
}

OneSaveState::~OneSaveState()
{
    for (auto &it : this->buttons)
    {
        delete it.second;
    }
}


void OneSaveState::initFonts()
{
    if (!this->font.loadFromFile(this->stateData->localpath+"Fonts/Caveat.ttf"))
    {
        throw("ERROR: Nie udalo sie zaladowac czcionki");
    }
}


void OneSaveState::initGui()
{
    const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

    this->background.setSize(sf::Vector2f(static_cast<float>(vm.width),static_cast<float>(vm.height)));

    if (!this->backgroundTexture.loadFromFile(this->stateData->localpath+"Images/LS.png"))
    {
        throw "ERROR::MAIN_MENU::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
    }

    this->title.setPosition(sf::Vector2f(static_cast<float>(gui::calcX(15.f,vm)),static_cast<float>(gui::calcY(9.f,vm))));
    this->title.setString("Zapis:  "+saveGamePtr->getSaveName());
    this->title.setFont(this->font);
    this->title.setStyle(1);
    this->title.setCharacterSize(gui::calcCharSize(vm,30));
    this->title.setFillColor(sf::Color(50,50,50,255));

    this->background.setTexture(&this->backgroundTexture);




    sf::Text* temp = new sf::Text("Wygrane: "+std::to_string(saveGamePtr->win_games)+"/"+std::to_string(saveGamePtr->win_games+saveGamePtr->loss_games),this->font, gui::calcCharSize(vm,70));
    temp->setPosition(sf::Vector2f(static_cast<float>(gui::calcX(19.f,vm)),static_cast<float>(gui::calcY(23.f,vm)+gui::calcCharSize(vm,110))));
    temp->setFillColor(sf::Color(70, 70, 70, 255));
    texts.push_back(temp);


    sf::Text* temp1 = new sf::Text("Czas gry: "+std::to_string(saveGamePtr->playtime)+"min",this->font, gui::calcCharSize(vm,70));
    temp1->setPosition(sf::Vector2f(static_cast<float>(gui::calcX(19.f,vm)),static_cast<float>(gui::calcY(30.f,vm)+gui::calcCharSize(vm,110))));
    temp1->setFillColor(sf::Color(70, 70, 70, 255));
    texts.push_back(temp1);

    sf::Text* temp2 = new sf::Text("Aktualne id gry: "+std::to_string(saveGamePtr->current_password_id),this->font, gui::calcCharSize(vm,70));
    temp2->setPosition(sf::Vector2f(static_cast<float>(gui::calcX(19.f,vm)),static_cast<float>(gui::calcY(37.f,vm)+gui::calcCharSize(vm,110))));
    temp2->setFillColor(sf::Color(70, 70, 70, 255));
    texts.push_back(temp2);




    //Exit
    auto* ButtonInitParams = new gui::ButtonParams;
    ButtonInitParams->x =  gui::calcX(10.f, vm);
    ButtonInitParams->y =  gui::calcY(81.5f, vm);
    ButtonInitParams->width = static_cast<float>(gui::calcCharSize(vm,50)*7);
    ButtonInitParams->height = static_cast<float>(gui::calcCharSize(vm,50)*1.2);
    ButtonInitParams->font = &this->font;
    ButtonInitParams->character_size = gui::calcCharSize(vm);
    ButtonInitParams->hoverScale = 1.2f;
    ButtonInitParams->activeScale = 1.1f;
    ButtonInitParams->text_idle_color= sf::Color(40, 40, 40, 255);
    ButtonInitParams->text_hover_color= sf::Color(25, 25, 25, 255);
    ButtonInitParams->text_active_color= sf::Color(10, 10, 10, 255);
    ButtonInitParams->text = L"Wróć";


    this->buttons[QUIT] = new gui::Button(ButtonInitParams);

    ButtonInitParams->x =  gui::calcX(25.f, vm);
    if(saveGamePtr->current_password_id==0)
        ButtonInitParams->text = L"Nowa gra";
    else{
        ButtonInitParams->text = L"Kontynnuj";
    }


    this->buttons[PLAY] = new gui::Button(ButtonInitParams);

    delete ButtonInitParams;
}


void OneSaveState::resetGui()
{
    for (auto &it : this->buttons)
    {
        delete it.second;
    }
    this->buttons.clear();
    this->initGui();
}


void OneSaveState::updateButtons(const float& dt)
{
    if (this->buttons[QUIT]->isPressed())
    {
        this->endState();
    }
    if (this->buttons[PLAY]->isPressed())
    {
        //this->endState();
        GameState * temp = new GameState(this->stateData);
        this->states->push(temp);
    }

    for (auto &it : this->buttons)
    {
        it.second->update(this->mousePosWindow,dt);
    }
}


void OneSaveState::update(const float& dt)
{
    this->updateMousePositions();
    if(this->stateData->gfxSettings->resolution.width != background.getSize().x || this->stateData->gfxSettings->resolution.height != background.getSize().y){
        resetGui();
    }
    this->updateButtons(dt);
}


void OneSaveState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    target->draw(this->background);
    target->draw(this->title);

    //Renderowanie buttonów
    for (auto &it : this->buttons)
    {
        it.second->render(*target);
    }

    for (auto &it : this->texts)
    {
        target->draw(*it);
    }
}



