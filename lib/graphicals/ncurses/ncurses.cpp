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

void Ncurses::update(std::map<std::string, IGameModule::Entity> entities)
{
    if (entities.size() == 0) {
        return;
    }
    if (entities.find("close") != entities.end()) {
        return;
    }
}

std::string Ncurses::getEvent()
{
    char c = getch();
    std::string val = std::string(&c);
    return val;
}

const std::string & Ncurses::getName() const
{
    return _name;
}

extern "C" IDisplayModule *create(void)
{
    return new  Ncurses();
}

extern "C" std::string getType(void)
{
    return "Graphic";
}

extern "C" void destroy(IDisplayModule* obj) {
    delete obj;
}
