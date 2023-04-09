/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-arcade-adam.elaoumari [WSL : Ubuntu]
** File description:
** nibbler
*/

#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_
#include "AGameModule.hpp"

class Nibbler : public AGameModule {
    public:
        Nibbler();
        ~Nibbler();
        void update(std::string key);
        const std::string &getName() const{return _name;};
        void resetGame(void);
        void changeLevel(void);

    protected:
        void move(void);
        void dataToEntity(void);
        void moveHead(int x, int y, bool eat, IGameModule::DIRECTION direction);
        int chooseSprite (float x, float y, int value);
        void snakePart(std::vector<int> value, float x, float y, int row, int i);
        void getInfoSnake (std::vector<std::string> map);
        int tryMoveHere(IGameModule::DIRECTION direction);
        int automaticMove(void);
        std::vector<std::string> getTextures(void);
        void elapsedTime(int time);
        int _head_x = 0;
        int _head_y = 0;
        int _size_snake = 0;
        int _apple_remain = 0;
        int countdown = 60;
        int level = 1;
        IGameModule::DIRECTION _next_direction = IGameModule::DIRECTION::RIGHT;
        std::string _name = "Nibbler";
};

#endif /* !NIBBLER_HPP_ */
