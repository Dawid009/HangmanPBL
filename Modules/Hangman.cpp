#include "Hangman.h"
#include "GraphicsSettings.h"

Hangman::Hangman(GraphicsSettings *settings) : gfxSettings(settings) {
    initHangman();
}

Hangman::~Hangman() {

}

void Hangman::initHangman() {
    const sf::VideoMode& vm = this->gfxSettings->resolution;

    renderTexture = new sf::RenderTexture();
    renderTexture->create(180.f, 500.f);
    renderTexture->clear(sf::Color::Transparent);

    constexpr char color = 40;

    line = new sf::RectangleShape(sf::Vector2f(5.f,140.f));
    line->setPosition(sf::Vector2f(90.f,0.f));
    line->setFillColor(sf::Color(color,color,color,255));

    head = new sf::CircleShape (30.f);
    head->setPosition(sf::Vector2f(65.f,135.f));
    head->setFillColor(sf::Color(color,color,color,0));

    body = new sf::RectangleShape(sf::Vector2f(12.f,110.f));
    body->setPosition(sf::Vector2f(85.f,170.f));
    body->setFillColor(sf::Color(color,color,color,0));

    arm1 = new sf::RectangleShape(sf::Vector2f(8.f,80.f));
    arm1->setPosition(sf::Vector2f(87.f,190.f));
    arm1->setFillColor(sf::Color(color,color,color,0));
    arm1->setRotation(30);

    arm2 = new sf::RectangleShape(sf::Vector2f(8.f,80.f));
    arm2->setPosition(sf::Vector2f(87.f,190.f));
    arm2->setFillColor(sf::Color(color,color,color,0));
    arm2->setRotation(-30);

    leg1= new sf::RectangleShape(sf::Vector2f(8.f,80.f));
    leg1->setPosition(sf::Vector2f(87.f,270.f));
    leg1->setFillColor(sf::Color(color,color,color,0));
    leg1->setRotation(30);

    leg2 = new sf::RectangleShape(sf::Vector2f(8.f,80.f));
    leg2->setPosition(sf::Vector2f(87.f,270.f));
    leg2->setFillColor(sf::Color(color,color,color,0));
    leg2->setRotation(-30);

    renderTexture->draw(*line);
    renderTexture->draw(*head);
    renderTexture->draw(*body);
    renderTexture->draw(*arm1);
    renderTexture->draw(*arm2);
    renderTexture->draw(*leg1);
    renderTexture->draw(*leg2);
    renderTexture->display();

    sprite = new sf::Sprite(renderTexture->getTexture());
    sprite->setPosition(sf::Vector2f(gui::calcX(75,vm),(vm.height/800.f)*60));
    sprite->scale((vm.width/1280.f),(vm.height/800.f));
}

void Hangman::update(const float &dt) {

}

void Hangman::render(sf::RenderTarget *target) {
    target->draw(*sprite);
}

void Hangman::setLevel(short level) {
    const unsigned char color = 40;
    renderTexture->clear(sf::Color::Transparent);
    renderTexture->draw(*line);
    switch(level)
    {
        case 0:
            head->setFillColor(sf::Color(color,color,color,0));
            body->setFillColor(sf::Color(color,color,color,0));
            arm1->setFillColor(sf::Color(color,color,color,0));
            arm2->setFillColor(sf::Color(color,color,color,0));
            leg1->setFillColor(sf::Color(color,color,color,0));
            leg2->setFillColor(sf::Color(color,color,color,0));
            break;
        case 6:
            leg2->setFillColor(sf::Color(color,color,color,254));
            renderTexture->draw(*leg2);
        case 5:
            leg1->setFillColor(sf::Color(color,color,color,254));
            renderTexture->draw(*leg1);
        case 4:
            arm2->setFillColor(sf::Color(color,color,color,254));
            renderTexture->draw(*arm2);
        case 3:
            arm1->setFillColor(sf::Color(color,color,color,254));
            renderTexture->draw(*arm1);
        case 2:
            body->setFillColor(sf::Color(color,color,color,254));
            renderTexture->draw(*body);
        case 1:
            head->setFillColor(sf::Color(color,color,color,254));
            renderTexture->draw(*head);
    }
    renderTexture->display();
    sprite->setTexture(renderTexture->getTexture());
    std::cout<<"miss level:"<<level;
}
