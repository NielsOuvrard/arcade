/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-arcade-adam.elaoumari
** File description:
** snake
*/

#include "snake.hpp"

Snake::Snake()
{
    generateGrid(100);
    float y = 0, x = 0;
    int row = 0;
    x = 600, y = 3;
}

Snake::~Snake()
{
}

void print_grid(std::vector<std::string> grid)
{
    for (std::string val : grid) {
        std::cout << val << std::endl;
    }
}
#include <unistd.h>

void Snake::update(std::string key)
{
    if (key.empty()) {
        if (_direction == DIRECTION::RIGHT) {
            for (auto &grid : _grid) {
                for (int i = 0; grid[i]; i++) {
                    if (grid[i] == 'H' && i + 1 < grid.size()) {
                        grid[i] = ' ';
                        grid[i + 1] = 'H';
                        // _entities["head"].x += 1;
                        break;
                    }
                }
            }
        }
        else if (_direction == DIRECTION::LEFT) {

        }
        else if (_direction == DIRECTION::UP) {

        }
        else if (_direction == DIRECTION::DOWN) {

        }
    }
    if (key == "close") {
        // _gameStatus = FINISHED;
    }
    if (key == "UpArrow") {
        // _entities["snake-head"].y -= 0.03;
        _direction = DIRECTION::UP;
    }
    if (key == "DownArrow") {
        // _entities["snake-head"].y += 0.03;
        _direction = DIRECTION::DOWN;
    }
    if (key == "LeftArrow") {
        // _entities["sknake-head"].x -= 5;
        _direction = DIRECTION::LEFT;
    }
    if (key == "RightArrow") {
        // _entities["snake-head"].x += 5;
        _direction = DIRECTION::RIGHT;
    }
    // print_grid(_grid);
    sleep(1);
}

const std::string &Snake::getName() const
{
    return _name;
}

extern "C" IGameModule *create(void)
{
    return new Snake();
}

extern "C" std::string getType(void)
{
    return "Game";
}

extern "C" void destroy(IGameModule* obj) {
    delete obj;
}
