#include "Hangman.h"
#include "GraphicsSettings.h"

#define HEAD 0
#define BODY 1
#define ARM1 2
#define ARM2 3
#define LEG1 4
#define LEG2 5

Hangman::Hangman(GraphicsSettings *settings) : gfxSettings(settings) {
    initHangman();
}

Hangman::~Hangman() {
    //Zwalnianie pamieci
    delete line;
    delete renderTexture;
    delete sprite;
    delete gfxSettings;
    for(auto part : hangman_parts){
        delete part;
    }
}

void Hangman::initHangman() {
    const sf::VideoMode& vm = this->gfxSettings->resolution;

    renderTexture = new sf::RenderTexture();
    renderTexture->create(180.f, 500.f);
    renderTexture->clear(sf::Color::Transparent);

    constexpr char color{40};

    line = new sf::RectangleShape(sf::Vector2f(5.f,140.f));
    line->setPosition(sf::Vector2f(90.f,0.f));
    line->setFillColor(sf::Color(color,color,color,255));

    hangman_parts[HEAD] = new sf::CircleShape (30.f);
    hangman_parts[HEAD]->setPosition(sf::Vector2f(65.f,135.f));

    hangman_parts[BODY] = new sf::RectangleShape(sf::Vector2f(12.f,110.f));
    hangman_parts[BODY]->setPosition(sf::Vector2f(85.f,170.f));

    hangman_parts[ARM1] = new sf::RectangleShape(sf::Vector2f(8.f,80.f));
    hangman_parts[ARM1]->setPosition(sf::Vector2f(87.f,190.f));
    hangman_parts[ARM1]->setRotation(30);

    hangman_parts[ARM2] = new sf::RectangleShape(sf::Vector2f(8.f,80.f));
    hangman_parts[ARM2]->setPosition(sf::Vector2f(87.f,190.f));
    hangman_parts[ARM2]->setRotation(-30);

    hangman_parts[LEG1]= new sf::RectangleShape(sf::Vector2f(8.f,80.f));
    hangman_parts[LEG1]->setPosition(sf::Vector2f(87.f,270.f));
    hangman_parts[LEG1]->setRotation(30);

    hangman_parts[LEG2] = new sf::RectangleShape(sf::Vector2f(8.f,80.f));
    hangman_parts[LEG2]->setPosition(sf::Vector2f(87.f,270.f));
    hangman_parts[LEG2]->setRotation(-30);

    for(auto part : hangman_parts){
        part->setFillColor(sf::Color(color,color,color,0));
        renderTexture->draw(*part);
    }

    renderTexture->draw(*line);
    renderTexture->display();

    sprite = new sf::Sprite(renderTexture->getTexture());
    sprite->setPosition(sf::Vector2f(gui::calcX(75,vm),(static_cast<float>(vm.height)/800.f)*60));
    sprite->scale((static_cast<float>(vm.width)/1280.f),(static_cast<float>(vm.height)/800.f));
}

void Hangman::update(const float &dt) {

}

void Hangman::render(sf::RenderTarget *target) {
    target->draw(*sprite);
}

void Hangman::setLevel(uint8_t level) {
    const unsigned char color{40};
    renderTexture->clear(sf::Color::Transparent);
    renderTexture->draw(*line);

    sf::Color temp_color_invisible{color, color, color, 0};
    sf::Color temp_color_visible{color,color,color,255};

    switch(level)
    {
        case 0:
            hangman_parts[HEAD]->setFillColor(temp_color_invisible);
            hangman_parts[BODY]->setFillColor(temp_color_invisible);
            hangman_parts[ARM1]->setFillColor(temp_color_invisible);
            hangman_parts[ARM2]->setFillColor(temp_color_invisible);
            hangman_parts[LEG1]->setFillColor(temp_color_invisible);
            hangman_parts[LEG2]->setFillColor(temp_color_invisible);
            break;
        case 6:
            hangman_parts[LEG2]->setFillColor(temp_color_visible);
        case 5:
            hangman_parts[LEG1]->setFillColor(temp_color_visible);
        case 4:
            hangman_parts[ARM2]->setFillColor(temp_color_visible);
        case 3:
            hangman_parts[ARM1]->setFillColor(temp_color_visible);
        case 2:
            hangman_parts[BODY]->setFillColor(temp_color_visible);
        case 1:
            hangman_parts[HEAD]->setFillColor(temp_color_visible);
        default:
            break;
    }

    for(auto part : hangman_parts){
        renderTexture->draw(*part);
    }
    renderTexture->display();
    sprite->setTexture(renderTexture->getTexture());
}
