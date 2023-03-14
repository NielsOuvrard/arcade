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

#include "../../../src/display/IDisplay.hpp"

class Sfml : public IDisplayModule {
    public:
        Sfml();
        ~Sfml();
        void init();
        void stop();
        void draw();

    protected:
        // sf::RenderWindow _window;
        // sf::RenderWindow window (sf::VideoMode(500,200) , "ma fenetre");
        sf::RenderWindow _window;
        sf::Event _event;
    private:
};
