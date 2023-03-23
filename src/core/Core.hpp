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
#include <unistd.h>
#include <map>
#include <memory>
#include "DLLoader.hpp"
#include "IDisplayModule.hpp"
#include "AGameModule.hpp"
#include "Menu.hpp"
class Core {
    public:
        Core(const std::string displayLibPath);
        ~Core();
        std::vector<std::string> getGamesLibs () const { return gameLibs;}
        std::vector<std::string> getGfxLibs () const { return gfxLibs;}
        void displayMenu();
        void mainLoop();
        void gameMenuLoop();
        void endGameLoop();

    protected:
    private:
        std::vector<std::string> gameLibs;
        std::vector<std::string> gfxLibs;
        std::vector<std::string> menuLibs;
        std::vector<IGameModule *> games;
        int currentGameIndex = 0;
        int currentDisplayIndex = 0;
        int currentMenuIndex = 0;
        std::vector<IDisplayModule *> displayList;
        std::vector<IGameModule *> gameList;
        std::vector<IGameModule *> menuList;
        IDisplayModule *selectedDisplay = nullptr;
        IGameModule *selectedGame = nullptr;
        IGameModule *selectedMenu = nullptr;
};

#endif /* !CORE_HPP_ */
