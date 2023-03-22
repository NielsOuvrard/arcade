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
    use_default_colors();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(0);
    keyok(27, TRUE); // ESC
    keyok(32, TRUE); // SPACE
    keyok(10, TRUE); // ENTER
    keyok(127, TRUE); // BACKSPACE
    keyok(265, TRUE);

    keyok(265, TRUE); // UP
    keyok(264, TRUE); // DOWN
    keyok(263, TRUE); // LEFT
    keyok(262, TRUE); // RIGHT

    keyok(259, TRUE); // F1
    keyok(260, TRUE); // F2

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

int Ncurses::colorExistInList(color_t color)
{
    int i = 0;
    for (auto const &c : _list_colors) {
        if (c.red == color.red
        && c.green == color.green
        && c.blue == color.blue)
            return i;
        i++;
    }
    return -1;
}

int Ncurses::pairExistInList(int color_1, int color_2)
{
    int i = 0;
    for (auto const &c : _list_pair_colors) {
        if (c.first == color_1 && c.second == color_2)
            return i;
        i++;
    }
    return -1;
}
#include <iostream>
#include <fstream>
#include <string>

// wite a function who write at the end of a file
void writeAtEnd(std::string str)
{
    std::ofstream file;
    file.open("file.txt", std::ios::app);
    file << str << std::endl;
    file.close();
}

int Ncurses::addColorToList(color_t color_1, color_t color_2)
{
    int index_color_1 = colorExistInList(color_1);
    int index_color_2 = colorExistInList(color_2);
    if (index_color_1 >= 0 && index_color_2 >= 0) {
        int index = pairExistInList(index_color_1, index_color_2);
        if (index >= 0)
            return index;
        _list_pair_colors.push_back({index_color_1, index_color_2});
        init_pair(_list_pair_colors.size() - 1, index_color_1, index_color_2);
        // writeAtEnd("both exist " + std::to_string(index_color_1) + " " + std::to_string(index_color_2)
        // + "\tcolor_1 " + std::to_string((color_1.red)) + " " + std::to_string((color_1.green)) + " " + std::to_string((color_1.blue))
        // + "\tcolor_2 " + std::to_string((color_2.red)) + " " + std::to_string((color_2.green)) + " " + std::to_string((color_2.blue))
        // );
        return _list_pair_colors.size() - 1;
    }
    if (index_color_1 < 0) {
        _list_colors.push_back(color_1);
        index_color_1 = _list_colors.size() - 1;
        // writeAtEnd("color : " + std::to_string(index_color_1) + " = " + std::to_string(color_1.red / 255) + " " + std::to_string(color_1.green / 255) + " " + std::to_string(color_1.blue));
        init_color(index_color_1, (color_1.red / 255) * 1000, (color_1.green / 255) * 1000, (color_1.blue / 255) * 1000);
    }
    if (index_color_2 < 0) {
        _list_colors.push_back(color_2);
        index_color_2 = _list_colors.size() - 1;
        // writeAtEnd("color : " + std::to_string(index_color_2) + " = " + std::to_string(color_1.red / 255) + " " + std::to_string(color_1.green / 255) + " " + std::to_string(color_1.blue));
        init_color(index_color_2, (color_2.red / 255) * 1000, (color_2.green / 255) * 1000, (color_2.blue / 255) * 1000);
    }
    // writeAtEnd(std::to_string(index_color_1) + " " + std::to_string(index_color_2)
    // + "\tcolor_1 " + std::to_string((color_1.red)) + " " + std::to_string((color_1.green)) + " " + std::to_string((color_1.blue))
    // + "\tcolor_2 " + std::to_string((color_2.red)) + " " + std::to_string((color_2.green)) + " " + std::to_string((color_2.blue))
    // );
    _list_pair_colors.push_back({index_color_1, index_color_2});
    init_pair(_list_pair_colors.size() - 1, index_color_1, index_color_2);
    return _list_pair_colors.size() - 1;
}

int Ncurses::handleColor(IGameModule::Entity e)
{
    int id = addColorToList(e.color_fg, e.color_bg);
    attron(COLOR_PAIR(id));
    return id;
}

void Ncurses::update(std::map<std::string, IGameModule::Entity> entities)
{
    erase();
    int i = 0;
    for (auto const &entity : entities) {
        if (entity.second.text.length()) {
            IGameModule::Entity e = entity.second;
            int id = handleColor(e);
            if (e.bold && e.underline) {
                 attron(A_BOLD);
                 attron(A_UNDERLINE);
            }
            mvprintw((int)e.y, (int)e.x, "%s", e.text.c_str());
            attroff(COLOR_PAIR(id));
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
    if (c == KEY_F(1))
        return "F1";
    if (c == KEY_F(2))
        return "F2";
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

void Ncurses::saveTextures(const std::vector<std::string> &path_texture)
{
    (void)path_texture;
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
