/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-arcade-adam.elaoumari [WSL : Ubuntu]
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_
#include <iostream>
#include <istream>
#include <sstream>
#include <vector>
#include <filesystem>
#include <map>
#include "DLLoader.hpp"
#include "IDisplay.hpp"
#include "IGameModule.hpp"
#include "Menu.hpp"
class Core {
    public:
        Core(const std::string displayLibPath);
        ~Core();
        std::vector<std::string> getGamesLibs () const { return gameLibs;}
        std::vector<std::string> getGfxLibs () const { return gfxLibs;}
        void displayMenu();
        void mainLoop();
    protected:
    private:
        std::vector<std::string> gameLibs;
        std::vector<std::string> gfxLibs;
        DLLoader<IDisplayModule> *displayLib;
        DLLoader<IGameModule> *gameLib;
        std::string selectedGameLib;
        std::string selectedDisplayLib;
};

#endif /* !CORE_HPP_ */
