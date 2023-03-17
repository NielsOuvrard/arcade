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
        enum DIRECTION {
            UP,
            DOWN,
            LEFT,
            RIGHT
        };
        struct box {
            int new_x;
            int new_y;
            int x;
            int y;
        } typedef t_box;
        Nibbler();
        ~Nibbler();
        void startGame() ;
        bool isGameOver();
        void update(std::string key);
        std::map<std::string, Entity> getInfos() { return entities;};
        GAME_STATUS getGameStatus() {return status;};
        void generateGrid(int lenght);
        std::vector<std::vector<int>> getGrid() const {return grid;};
        DIRECTION getDirection() {return _direction;};
    protected:
        GAME_STATUS status;
        std::map<std::string, Entity> entities;
        std::vector<std::vector<int>> grid;
        std::vector<std::vector<t_box>> boxes;
        DIRECTION _direction = DIRECTION::RIGHT;
};

#endif /* !NIBBLER_HPP_ */
