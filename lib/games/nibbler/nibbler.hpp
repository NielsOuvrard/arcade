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
        struct box {
            int new_x;
            int new_y;
            int x;
            int y;
        } typedef t_box;

        Nibbler();
        ~Nibbler();
        void update(std::string key);

    protected:
        void move(void);
        void dataToEntity(void);
        void moveHead(int x, int y, bool eat, IGameModule::DIRECTION direction);
        int chooseSprite (float x, float y, int value);
        void snakePart(std::vector<int> value, float x, float y, int row, int i);
        void getInfoSnake (std::vector<std::string> map);
        int tryMoveHere(IGameModule::DIRECTION direction);

        std::vector<std::string> getTextures(void);
        int _head_x = 0;
        int _head_y = 0;
        int _size_snake = 0;
        int _apple_remain = 0;
        IGameModule::DIRECTION _next_direction = IGameModule::DIRECTION::RIGHT;
};

#endif /* !NIBBLER_HPP_ */
