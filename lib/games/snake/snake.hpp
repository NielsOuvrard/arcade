/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-arcade-adam.elaoumari
** File description:
** snake
*/

#pragma once

#include "AGameModule.hpp"

class Snake : public AGameModule {
    public:
        Snake();
        ~Snake();
        void update(std::string key);
        const std::string &getName() const;
        std::vector<std::string> getTextures(void){return std::vector<std::string>();};
    protected:
    private:
        std::string _name = "Snake";
        int _speed = 1;
};
