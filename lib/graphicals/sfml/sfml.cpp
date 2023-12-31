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
    _window = std::unique_ptr<sf::RenderWindow>(
        new sf::RenderWindow(sf::VideoMode(1920, 1080), "Arcade - SFML")
    );
    _window->setVisible(false);
    std::cout << "SFML constructor" << std::endl;
    _window->setVisible(true);
    _window->setKeyRepeatEnabled(false);
    font.loadFromFile("font.ttf");
    _music.openFromFile("music.ogg");
    _music.setVolume(35);
    _music.setLoop(true);
    _music.play();
}

void Sfml::stop()
{
    _music.stop();
    _window->setVisible(false);
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
            sprite.scale(sf::Vector2f(2, 2));
            sprite.setPosition(sf::Vector2f((entity.x * 200) * 0.16, (entity.y * 200) * 0.16));
            _window->draw(sprite);
        }
    }
    entities.clear();
}

std::string Sfml::getEvent()
{
    sf::Event event;
    while (_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            return "close";
        if (event.type == sf::Event::MouseButtonPressed) {
            return "click";
        }
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
                case 36:
                    return "ESC";
            }
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                std::string val = "MouseClick " +
                std::to_string(event.mouseButton.x / (_window->getSize().x / 11)) + " " +
                std::to_string(event.mouseButton.y / (_window->getSize().y / 11));
                std::cout << val << std::endl;
                return val;
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

void Sfml::resetDisplay(void)
{
    _textures.clear();
}

extern "C" IDisplayModule *create(void)
{
    return new Sfml();
}


extern "C" std::string getType() {
    return "Graphic";
}