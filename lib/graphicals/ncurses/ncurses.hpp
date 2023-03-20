/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-arcade-adam.elaoumari
** File description:
** ncurses
*/

#pragma once

#include <ncurses.h>
#include "IDisplayModule.hpp"

class Ncurses : public IDisplayModule {
    public:
        Ncurses();
        ~Ncurses();
        void init();
        void stop();
        void draw();
        void update(std::map<std::string, IGameModule::Entity> entities);
        std::string getEvent();
        const std::string &getName() const;

    protected:
        std::string _name = "SFML";
        int event;
    private:
};
