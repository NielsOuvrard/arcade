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
    // mvprintw(0, 0, "Hello World !!!");
    refresh();
}

void Ncurses::update(std::map<std::string, IGameModule::Entity> entities)
{
    int i = 0;
    for (auto const &entity : entities) {
        if (entity.second.text.length()) {
            IGameModule::Entity e = entity.second;
            init_color(COLOR_RED, 1000 / e.red, 1000 / e.green, 1000 / e.blue);
            init_pair(1, COLOR_RED, COLOR_BLACK);
            attron(COLOR_PAIR(1));

            int y = ((int)e.y);
            if (e.bold && e.underline) {
                 attron(A_BOLD);
                 attron(A_UNDERLINE);
            }
            mvprintw(y, (int)e.x, "%s -> %d %d %d", e.text.c_str(), e.red, e.green, e.blue);
            attroff(COLOR_PAIR(1));
            attroff(A_UNDERLINE);
            attroff(A_BOLD);
        }
    }
}

std::string Ncurses::getEvent()
{
    int c;
    if (!(c = getch()))
        return "";
    if (c == KEY_BACKSPACE)
        return "close";

    // not work mac
    // if (c == 65)
    //     return "UpArrow";
    // if (c == 66)
    //     return "DownArrow";
    // if (c == 67)
    //     return "RightArrow";
    // if (c == 68)
    //     return "LeftArrow";
    // exit(c);

    if (c == KEY_LEFT)
        return "LeftArrow";
    if (c == KEY_RIGHT)
        return "RightArrow";
    if (c == KEY_UP)
        return "UpArrow";
    if (c == KEY_DOWN)
        return "DownArrow";

    if (c == KEY_ENTER)
        return "Enter";
    if (c == KEY_BACKSPACE)
        return "Backspace";
    if (isascii(c)) {
        std::string val = {(char)c};
        return val;
    }
    return "";
}

const std::string & Ncurses::getName() const
{
    return _name;
}

extern "C" IDisplayModule *create(void)
{
    return new Ncurses();
}

extern "C" std::string getType(void)
{
    return "Graphic";
}

extern "C" void destroy(IDisplayModule* obj) {
    delete obj;
}
