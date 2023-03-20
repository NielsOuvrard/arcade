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
        std::vector<std::vector<t_box>> boxes;
};

#endif /* !NIBBLER_HPP_ */
