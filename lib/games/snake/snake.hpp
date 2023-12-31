/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-arcade-adam.elaoumari [WSL : Ubuntu]
** File description:
** Snake
*/

#ifndef SNAKE_HPP_
#define SNAKE_HPP_
#include "AGameModule.hpp"

class Snake : public AGameModule {
    public:
        Snake();
        ~Snake();
        void update(std::string key);
        const std::string &getName() const{return _name;};
        void resetGame(void);
    protected:
        void move(void);
        void dataToEntity(void);
        void moveHead(int x, int y, bool eat, IGameModule::DIRECTION direction);
        int chooseSprite (float x, float y, int value);
        void snakePart(std::vector<int> value, float x, float y, int row, int i);
        void getInfoSnake (std::vector<std::string> map);
        int tryMoveHere(IGameModule::DIRECTION direction);
        void generateRandomApple();
        std::vector<std::string> getTextures(void);
        int _head_x = 0;
        int _head_y = 0;
        int _size_snake = 0;
        IGameModule::DIRECTION _next_direction = IGameModule::DIRECTION::RIGHT;
        std::string _name = "Snake";
};

#endif /* !SNAKE_HPP_ */
