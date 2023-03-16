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
    start_color();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(0);
    keyok(27, TRUE); // ESC
    keyok(32, TRUE); // SPACE
    keyok(10, TRUE); // ENTER
    keyok(127, TRUE); // BACKSPACE
    nodelay(stdscr, TRUE);
    cbreak();
}

void Ncurses::stop()
{
    endwin();
}

void Ncurses::draw()
{
    refresh();
}

#define COLOR_FG 1
#define COLOR_BG 2

void Ncurses::update(std::map<std::string, IGameModule::Entity> entities)
{
    int i = 0;
    for (auto const &entity : entities) {
        if (entity.second.text.length()) {
            IGameModule::Entity e = entity.second;
            color_t color_fg = e.color_fg;
            color_t color_bg = e.color_bg;
            init_color(COLOR_FG, (color_fg.red / 255) * 1000, (color_fg.green / 255) * 1000, (color_fg.blue / 255) * 1000);
            init_color(COLOR_BG, (color_bg.red / 255) * 1000, (color_bg.green / 255) * 1000, (color_bg.blue / 255) * 1000);
            init_pair(1, COLOR_FG, COLOR_BG);
            attron(COLOR_PAIR(1));

            if (e.bold && e.underline) {
                 attron(A_BOLD);
                 attron(A_UNDERLINE);
            }
            mvprintw((int)e.y, (int)e.x, "%s", e.text.c_str());
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
    if (c == KEY_LEFT)
        return "LeftArrow";
    if (c == KEY_RIGHT)
        return "RightArrow";
    if (c == KEY_UP)
        return "UpArrow";
    if (c == KEY_DOWN)
        return "DownArrow";

    if (c == 27)
        return "close";
    if (c == KEY_ENTER || c == 10)
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
