/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-arcade-adam.elaoumari [WSL : Ubuntu]
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_
#include "Core.hpp"
#include "AGameModule.hpp"
class Menu : public AGameModule {
    public:
        Menu(std::vector<std::string> gameLibs, std::vector<std::string> gfxLibs);
        ~Menu();
        void update(std::string key);
        bool getSelectedStatus() {return (hasSelected && name.length() > 18);};
        int getSelectedGameLibIndex() const { return selectedGameIndex;};
        int getSelectedDisplayLibIndex() const {return selectedDisplayIndex;};
        std::vector<std::string> getTextures(void){return std::vector<std::string>();};
        const std::string &getName() const{return name;};
        void resetGame(void);
    protected:
        std::string name = "Enter your name : ";
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
