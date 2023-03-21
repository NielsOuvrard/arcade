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
    _window = new sf::RenderWindow;
    _window->create(sf::VideoMode(1920, 1080), "Arcade - SFML");
    _window->setKeyRepeatEnabled(false);
    font.loadFromFile("font.ttf");
}

void Sfml::stop()
{
    _window->close();
    delete _window;
}

void Sfml::draw()
{
    // in case of error
    if (!_window->isOpen()) {
        return;
    }
    // draw...

    _window->display();
}

void Sfml::update(std::map<std::string, IGameModule::Entity> entities)
{
    if (entities.size() == 0) {
        return;
    }
    _window->clear();
    for (auto const &val : entities) {
        IGameModule::Entity entity = val.second;
        if (entity.id_file == -1) {
            sf::Text text;
            if (entity.bold && entity.underline)
                text.setStyle(sf::Text::Bold | sf::Text::Underlined);
            text.setFont(font);
            text.setString(entity.text);
            sf::Color color(entity.color_fg.red, entity.color_fg.green, entity.color_fg.blue);
            text.setFillColor(color);
            text.setPosition(sf::Vector2f(entity.x * 100, entity.y * 100));
            text.setCharacterSize(60);
            _window->draw(text);
        } else {
            sf::Sprite sprite;
            sprite.setTexture(_textures[entity.id_file]);
            sprite.setPosition(sf::Vector2f((entity.x * 100) * 0.16, (entity.y * 100) * 0.16));
            _window->draw(sprite);
        }
    }
}

std::string Sfml::getEvent()
{
    sf::Event event;
    while (_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            return "close";
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode == '\n')
                return "Enter";
            if (event.text.unicode == 13)
                return "Enter";
            if (event.text.unicode == 27)
                return "ESC";
            if (event.text.unicode == 8) {
                return "Backspace";
            }
            if (event.text.unicode < 128) {
                char  c = static_cast<char>(event.text.unicode);
                std::string val = {c};
                return val;
            }
        } else if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case 71:
                    return "LeftArrow";
                case 72:
                    return "RightArrow";
                case 73:
                    return "UpArrow";
                case 74:
                    return "DownArrow";
                case 85:
                    return "F1";
                case 86:
                    return "F2";
            }
        }
    }
    return "";
}

void Sfml::saveTextures(const std::vector<std::string> &path_texture)
{
    for (auto const &val : path_texture) {
        sf::Texture texture;
        std::cout << "load texture: " << val << std::endl;
        texture.loadFromFile(val);
        _textures.push_back(texture);
    }
}

const std::string & Sfml::getName() const
{
    return _name;
}

extern "C" IDisplayModule *create(void)
{
    return new Sfml();
}

extern "C" void destroy(IDisplayModule* obj) {
    delete obj;
}

extern "C" std::string getType() {
    return "Graphic";
}