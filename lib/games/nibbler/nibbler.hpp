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
        void generateApple(void);
        void moveHead(int x, int y, bool generateApple);
        int chooseSprite (float x, float y, int value);
        void snakePart(std::vector<int> value, float x, float y, int row, int i);
        std::vector<std::string> getTextures(void);

        // std::vector<std::vector<t_box>> boxes;
        int _head_x = 0;
        int _head_y = 0;
        int _size_snake = 0;
};

#endif /* !NIBBLER_HPP_ */
