#include "SettingsState.h"


void SettingsState::initVariables()
{
    this->modes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::initFonts()
{
    if (!this->font.loadFromFile("Fonts/Caveat.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
    }
}

void SettingsState::initGui()
{
    const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

    this->background.setSize(
            sf::Vector2f
                    (
                            static_cast<float>(vm.width),
                            static_cast<float>(vm.height)
                    )
    );



    if (!this->backgroundTexture.loadFromFile("Images/background.jpg"))
    {
        throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
    }

    this->background.setTexture(&this->backgroundTexture);

    auto* ButtonInitParams = new gui::ButtonParams;

    ButtonInitParams->x =  gui::calcX(10.f, vm);
    ButtonInitParams->y =  gui::calcY(81.5f, vm);
    ButtonInitParams->width = gui::calcX(9.f, vm);
    ButtonInitParams->height = gui::calcY(6.f, vm);
    ButtonInitParams->font = &this->font;
    ButtonInitParams->text = "Back";
    ButtonInitParams->text_idle_color= sf::Color(40, 40, 40, 255);
    ButtonInitParams->text_hover_color= sf::Color(25, 25, 25, 255),
    ButtonInitParams->text_active_color= sf::Color(10, 10, 10, 255),
    ButtonInitParams->character_size = gui::calcCharSize(vm);
    ButtonInitParams->hoverScale = 1.2f;
    ButtonInitParams->activeScale = 1.1f;
    //ButtonInitParams->drawDebugBorder = true;
    this->buttons["BACK"] = new gui::Button(ButtonInitParams);


    ButtonInitParams->x =  gui::calcX(25.f, vm);
    ButtonInitParams->y =  gui::calcY(81.5f, vm);
    ButtonInitParams->text = "Apply & Save";
    this->buttons["APPLY"] = new gui::Button(ButtonInitParams);


    short active_id = 0;
    std::vector<std::string> modes_str;
    for (int i=0;i<modes.size();i++)
    {
        modes_str.push_back(std::to_string(this->modes[i].width) + 'x' + std::to_string(this->modes[i].height));
        if(this->modes[i]==vm){
            active_id=i;
        }
    }

    auto* DropdownParams = new gui::DropDownParams();
    DropdownParams->x = gui::calcX(43.f, vm);
    DropdownParams->y = gui::calcY(21.f, vm);
    DropdownParams->width = gui::calcX(9.4f, vm);
    DropdownParams->height = gui::calcY(4.5f, vm);
    DropdownParams->font = &font;
    DropdownParams->list = modes_str.data();
    DropdownParams->nrOfElements = modes_str.size();
    DropdownParams->character_size = gui::calcCharSize(vm,80);
    DropdownParams->id = active_id;

    this->dropDownLists["RESOLUTION"] = new gui::DropDownList(DropdownParams);

    std::vector<std::string> fullscreen_str;

    fullscreen_str.push_back("OFF");
    fullscreen_str.push_back("ON");

    DropdownParams->x = gui::calcX(12.f, vm);
    DropdownParams->id = this->stateData->gfxSettings->fullscreen?1:0;
    DropdownParams->list = fullscreen_str.data();
    DropdownParams->nrOfElements = fullscreen_str.size();
    this->dropDownLists["FULLSCREEN"] = new gui::DropDownList(DropdownParams);

    delete DropdownParams;

    this->optionsText.setFont(this->font);
    this->optionsText.setPosition(sf::Vector2f(gui::calcX(10.2f, vm), gui::calcY(15.7f, vm)));
    this->optionsText.setCharacterSize(gui::calcCharSize(vm, 70));
    this->optionsText.setFillColor(sf::Color(40, 40, 40, 250));
    this->optionsText.setStyle(1);
    this->optionsText.setString(
            "Fullscreen:    Vsync:    Antialiasing:    Resolution: "
    );
}

void SettingsState::resetGui()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
    this->buttons.clear();

   auto it2 = this->dropDownLists.begin();
    for (it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end(); ++it2)
    {
        delete it2->second;
    }
    this->dropDownLists.clear();

    this->initGui();
}

SettingsState::SettingsState(StateData* state_data)
        : State(state_data)
{
    this->initVariables();
    this->initFonts();
    this->initGui();
}

SettingsState::~SettingsState()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }

    auto it2 = this->dropDownLists.begin();
    for (it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end(); ++it2)
    {
        delete it2->second;
    }
}


void SettingsState::updateGui(const float & dt)
{
    for (auto &it : this->buttons)
    {
        it.second->update(this->mousePosWindow,dt);
    }

    if (this->buttons["BACK"]->isPressed())
    {
        this->endState();
    }

    if (this->buttons["APPLY"]->isPressed())
    {
        this->stateData->gfxSettings->resolution = this->modes[this->dropDownLists["RESOLUTION"]->getActiveElementId()];
        this->stateData->gfxSettings->fullscreen = this->dropDownLists["FULLSCREEN"]->getActiveElementId() != 0;
        this->stateData->gfxSettings->saveToFile("Config/graphics.ini");
        this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, this->stateData->gfxSettings->fullscreen?  sf::Style::Fullscreen :  sf::Style::Default);

        this->resetGui();
    }


    for (auto &it : this->dropDownLists)
    {
        it.second->update(this->mousePosWindow, dt);
    }

}

void SettingsState::update(const float& dt)
{
    this->updateMousePositions();
    this->updateGui(dt);
}


void SettingsState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    target->draw(this->background);

    for (auto &it : this->buttons)
    {
        it.second->render(*target);
    }

    for (auto &it : this->dropDownLists)
    {
        it.second->render(*target);
    }

    target->draw(this->optionsText);
}