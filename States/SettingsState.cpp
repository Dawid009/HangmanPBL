#include "SettingsState.h"

void SettingsState::initVariables()
{
    this->modes = sf::VideoMode::getFullscreenModes();
    const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
    fpsText = new sf::Text();

    fpsText->setString("");
    fpsText->setFont(this->font);
    fpsText->setCharacterSize(gui::calcCharSize(vm,70.f));
    fpsText->setPosition(sf::Vector2f(gui::calcX(0.5f,vm),gui::calcY(0.5f,vm)));
    fpsText->setFillColor(sf::Color(20, 20, 20, 255));
}

void SettingsState::initFonts()
{
    if (!this->font.loadFromFile(this->stateData->localpath+"Fonts/Caveat.ttf"))
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

    if (!this->backgroundTexture.loadFromFile(this->stateData->localpath+"Images/background.jpg"))
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
    ButtonInitParams->text = L"Wróc";
    ButtonInitParams->text_idle_color= sf::Color(40, 40, 40, 255);
    ButtonInitParams->text_hover_color= sf::Color(25, 25, 25, 255),
    ButtonInitParams->text_active_color= sf::Color(10, 10, 10, 255),
    ButtonInitParams->character_size = gui::calcCharSize(vm);
    ButtonInitParams->hoverScale = 1.2f;
    ButtonInitParams->activeScale = 1.1f;
    this->buttons["BACK"] = new gui::Button(ButtonInitParams);


    ButtonInitParams->x =  gui::calcX(25.f, vm);
    ButtonInitParams->y =  gui::calcY(81.5f, vm);
    ButtonInitParams->text = "Aplikuj i zapisz";
    this->buttons["APPLY"] = new gui::Button(ButtonInitParams);


    short active_id{0};
    std::vector<std::string> modes_str;
    for (int i{0};i<modes.size();i++)
    {
        modes_str.push_back(std::to_string(this->modes[i].width) + 'x' + std::to_string(this->modes[i].height));
        if(this->modes[i]==vm){
            active_id=i;
        }
    }


    auto* DropdownParams = new gui::DropDownParams();
    DropdownParams->x = gui::calcX(42.5f, vm);
    DropdownParams->y = gui::calcY(16.f, vm);
    DropdownParams->width = gui::calcX(9.f, vm);
    DropdownParams->height = gui::calcY(4.0f, vm);
    DropdownParams->font = &font;
    DropdownParams->list = modes_str.data();
    DropdownParams->nrOfElements = modes_str.size();
    DropdownParams->character_size = gui::calcCharSize(vm,90);
    DropdownParams->id = active_id;
    auto text = new std::wstring{L"Rozdzielczość"};
    DropdownParams->label = text;
    this->dropDownLists["RESOLUTION"] = new gui::DropDownList(DropdownParams);


    std::vector<std::string> fullscreen_str;
    fullscreen_str.emplace_back("OFF");
    fullscreen_str.emplace_back("ON");
    DropdownParams->x = gui::calcX(6.f, vm);
    DropdownParams->id = this->stateData->gfxSettings->fullscreen?1:0;
    DropdownParams->list = fullscreen_str.data();
    DropdownParams->nrOfElements = fullscreen_str.size();
    *text = L"Pełny ekran";
    this->dropDownLists["FULLSCREEN"] = new gui::DropDownList(DropdownParams);


    std::vector<std::string> vsync_str;
    vsync_str.emplace_back("OFF");
    vsync_str.emplace_back("ON");
    DropdownParams->x = gui::calcX(18.f, vm);
    DropdownParams->id = this->stateData->gfxSettings->contextSettings.antialiasingLevel?1:0;
    DropdownParams->list = vsync_str.data();
    DropdownParams->nrOfElements = vsync_str.size();
    *text = L"VSync";
    this->dropDownLists["VSYNC"] = new gui::DropDownList(DropdownParams);


    std::vector<std::string> aliasing_str;
    aliasing_str.emplace_back("OFF");
    aliasing_str.emplace_back("ON");
    DropdownParams->x = gui::calcX(30.f, vm);
    DropdownParams->id = this->stateData->gfxSettings->contextSettings.antialiasingLevel?1:0;
    DropdownParams->list = aliasing_str.data();
    DropdownParams->nrOfElements = aliasing_str.size();
    *text = L"Anti-aliasing";
    this->dropDownLists["ALIASING"] = new gui::DropDownList(DropdownParams);


    std::vector<std::string> fpscap_str;
    fpscap_str.emplace_back("MAX");
    fpscap_str.emplace_back("240");
    fpscap_str.emplace_back("120");
    fpscap_str.emplace_back("60");
    fpscap_str.emplace_back("30");
    fpscap_str.emplace_back("15");
    DropdownParams->x = gui::calcX(6.f, vm);
    DropdownParams->y= gui::calcY(40.f, vm);
    for(int i{0};i<6;i++){
        if(this->stateData->gfxSettings->frameRateLimit==fps[i])
        {
            DropdownParams->id = i;
            break;
        }
    }
    DropdownParams->list = fpscap_str.data();
    DropdownParams->nrOfElements = fpscap_str.size();
    *text = L"Limit FPS";
    this->dropDownLists["FPS"] = new gui::DropDownList(DropdownParams);


    std::vector<std::string> showfps_str;
    showfps_str.emplace_back("OFF");
    showfps_str.emplace_back("ON");
    DropdownParams->x = gui::calcX(18.f, vm);
    DropdownParams->y= gui::calcY(40.f, vm);
    DropdownParams->id = this->stateData->gfxSettings->showFps?1:0;
    DropdownParams->list = showfps_str.data();
    DropdownParams->nrOfElements = showfps_str.size();
    *text = L"Pokaż Fps";
    this->dropDownLists["SHOWFPS"] = new gui::DropDownList(DropdownParams);


    delete DropdownParams;
}

void SettingsState::resetGui()
{
    for (auto& it : buttons)
    {
        delete it.second;
    }
    this->buttons.clear();

    for (auto& it2: dropDownLists)
    {
        delete it2.second;
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

    for (auto &it : buttons)
    {
        delete it.second;
    }

    for (auto &it2 : dropDownLists)
    {
        delete it2.second;
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
        this->stateData->gfxSettings->contextSettings.antialiasingLevel = this->dropDownLists["ALIASING"]->getActiveElementId() !=0;
        this->stateData->gfxSettings->verticalSync = this->dropDownLists["VSYNC"]->getActiveElementId() !=0;
        this->stateData->gfxSettings->frameRateLimit = this->fps[this->dropDownLists["FPS"]->getActiveElementId()];
        this->stateData->gfxSettings->showFps= dropDownLists["SHOWFPS"]->getActiveElementId() !=0;
        this->stateData->gfxSettings->saveToFile(this->stateData->localpath+"Config/graphics.ini");
        this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, this->stateData->gfxSettings->fullscreen?  sf::Style::Fullscreen :  sf::Style::Titlebar | sf::Style::Close);
        this->window->setFramerateLimit(this->stateData->gfxSettings->frameRateLimit);
        this->resetGui();
    }

    for (auto &it : this->dropDownLists)
    {
        it.second->update(this->mousePosWindow, dt);
    }

    if(this->stateData->gfxSettings->showFps && delay>1.5f){
        fpsText->setString(std::to_string(static_cast<int>(1/dt)));
        delay=0;
    }else{
        delay+=dt;
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
    if(this->stateData->gfxSettings->showFps){
        target->draw(*fpsText);
    }
}