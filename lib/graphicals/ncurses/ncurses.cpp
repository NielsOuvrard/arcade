/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-arcade-adam.elaoumari
** File description:
** ncurses
*/

#include "ncurses.hpp"

Ncurses::Ncurses()
{
}

Ncurses::~Ncurses()
{
}

void Ncurses::init()
{
    initscr();
    noecho();
    cbreak();
}

void Ncurses::stop()
{
    endwin();
}

void Ncurses::draw()
{
    mvprintw(0, 0, "Hello World !!!");
    refresh();
}