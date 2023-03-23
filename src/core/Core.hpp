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
    class Error : public std::exception {
        public:
            Error(std::string val) noexcept : msg(val) {};
            const char *what() const noexcept override {return msg.c_str();}
        private:
            std::string msg;
    };
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
        std::vector<IGameModule *> gameList;
        std::vector<IGameModule *> menuList;
        std::vector<DLLoader<void> *> loadedLibs;
        std::vector<DLLoader<IDisplayModule> *> loadedLibsDisplay;
        IDisplayModule *selectedDisplay = nullptr;
        IGameModule *selectedGame = nullptr;
        IGameModule *selectedMenu = nullptr;
};

#endif /* !CORE_HPP_ */
