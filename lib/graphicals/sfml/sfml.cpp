/*
**
**  .M"""bgd `7MM"""YMM `7MMM.     ,MMF'`7MMF'
** ,MI    "Y   MM    `7   MMMb    dPMM    MM
** `MMb.       MM   d     M YM   ,M MM    MM
**   `YMMNq.   MM""MM     M  Mb  M' MM    MM
** .     `MM   MM   Y     M  YM.P'  MM    MM      ,
** Mb     dM   MM         M  `YM'   MM    MM     ,M
** P"Ybmmd"  .JMML.     .JML. `'  .JMML..JMMmmmmMMM
**
*/

#include "sfml.hpp"

Sfml::Sfml()
{
}

Sfml::~Sfml()
{
}

void Sfml::init()
{
    _window.create(sf::VideoMode(1280, 720), "Monitor");
}

void Sfml::stop()
{
    _window.close();
}

void Sfml::draw()
{
    if (!_window.isOpen()) {
        return;
    }
    // mettdre dans update
    // sf::Event event;
    // while (_window.pollEvent(event)) {
    //     if (event.type == sf::Event::Closed)
    //         _window.close();
    // }
    _window.clear();

    sf::RectangleShape rectangle(sf::Vector2f(120.f, 50.f));
    rectangle.setFillColor(sf::Color::White);
    rectangle.setPosition(sf::Vector2f(50, 70));
    _window.draw(rectangle);

    _window.display();
}


void Sfml::update(std::map<std::string, IGameModule::Entity> entities)
{
    if (entities.size() == 0) {
        return;
    }
    if (entities.find("close") != entities.end()) {
        _window.close();
    }
}

std::string Sfml::getEvent()
{
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            return "close";
            // _window.close();
    }
    return "";
}

const std::string & Sfml::getName() const
{
    return _name;
}

extern "C" IDisplayModule *entryPoint(void)
{
    return new Sfml();
}
