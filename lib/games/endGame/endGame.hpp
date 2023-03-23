/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-arcade-adam.elaoumari [WSL : Ubuntu]
** File description:
** GameMenu
*/

#ifndef MENU_HPP_
#define MENU_HPP_
#include "Core.hpp"
#include "AGameModule.hpp"

class EndGame : public AGameModule {
    public:
        EndGame();
        ~EndGame();
        void update(std::string key);
        bool getSelectedStatus() {return hasSelected;};
        std::string getSelectedOption() const { return options[selectedOptionIndex];};
        std::vector<std::string> getTextures();
        const std::string &getName() const{return _name;};

    protected:
        int selectedOptionIndex = 0;
        bool hasSelected = false;
        std::vector<std::string> options = {"Restart", "Menu","Quit"};
        std::string _name = "EndGame";
    private:
};

#endif /* !MENU_HPP_ */
