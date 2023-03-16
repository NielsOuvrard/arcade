/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-arcade-adam.elaoumari [WSL : Ubuntu]
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_
#include "Core.hpp"
class Menu  : public IGameModule {
    public:
        Menu(std::vector<std::string> gameLibs, std::vector<std::string> gfxLibs);
        ~Menu();
        bool isGameOver();
        void startGame() {
            status = IN_GAME;
        };
        void update(std::string key);
        std::map<std::string, Entity> getInfos() { return entities;};
        GAME_STATUS getGameStatus() { return status;};
        bool getSelectedStatus() {return hasSelected;};
        std::string getSelectedGameLib() const { return gameLibs[selectedGameIndex];};
        std::string getSelectedDisplayLib() const {return gfxLibs[selectedDisplayIndex];};
    protected:
        std::string name = "Enter your name : ";
        std::map<std::string, Entity> entities;
        GAME_STATUS status;
        int selectedGameIndex = 0;
        int selectedDisplayIndex = 0;
        bool isGameSelected = false;
        bool isDisplaySelected = false;
        bool hasSelected = false;
        std::vector<std::string> gameLibs;
        std::vector<std::string> gfxLibs;
    private:
};

#endif /* !MENU_HPP_ */
