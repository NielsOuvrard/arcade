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

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "IDisplayModule.hpp"

class Sfml : public IDisplayModule {
    public:
        Sfml();
        ~Sfml();
        void init();
        void stop();
        void update(std::map<std::string, IGameModule::Entity> entities);
        void draw();
        void saveTextures(const std::vector<std::string> &texture);
        std::string getEvent();
        const std::string &getName() const;

    protected:
        // sf::RenderWindow _window;
        // sf::RenderWindow window (sf::VideoMode(500,200) , "ma fenetre");
        sf::RenderWindow* _window = nullptr;
        sf::Event _event;
        std::string _name = "SFML";
        sf::Font font;
        std::vector<sf::Texture> _textures;
    private:
};
