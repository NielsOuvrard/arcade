/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-arcade-adam.elaoumari [WSL : Ubuntu]
** File description:
** nibbler
*/

#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_
#include "IGameModule.hpp"

class Nibbler : public IGameModule {
    public:
        Nibbler();
        ~Nibbler();
        void startGame();
        bool isGameOver();
        void update(std::string key);
        std::map<std::string, Entity> getInfos() { return entities;};
        GAME_STATUS getGameStatus() {return status;};
        void generateGrid(int lenght);
        std::vector<std::string> getGrid() const {return grid;};
    protected:
        GAME_STATUS status;
        std::map<std::string, Entity> entities;
        std::vector<std::string> grid;

};

#endif /* !NIBBLER_HPP_ */
