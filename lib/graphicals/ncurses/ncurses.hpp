/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-arcade-adam.elaoumari
** File description:
** ncurses
*/

#pragma once

#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <string>
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
        void saveTextures(const std::vector<std::string> &texture);
        int colorExistInList(color_t color);
        int pairExistInList(int color_1, int color_2);
        int addColorToList(color_t color_1, color_t color_2);
        int handleColor(IGameModule::Entity e);
        void resetDisplay(void);
    protected:
        std::string _name = "Ncurses";
        std::vector<color_t> _list_colors;
        std::vector<std::pair<int, int>> _list_pair_colors;
        WINDOW *_window = nullptr;
        SCREEN *_screen = nullptr;
        int event;
    private:
};
