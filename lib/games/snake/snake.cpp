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
    for (std::string value : _grid) {
        for (int i = 0; value[i]; i++) {
            if (value[i] == '-') {
                Entity newEntity = {
                    "lib/games/snake/files/snake/walls.png",
                    "#",
                    "",
                    x,
                    y,
                    false,
                    false,
                    {255, 0, 0},
                    {0, 0, 0},
                };
                std::cout << newEntity.y << std::endl;
                _entities.insert({std::to_string(i) + "walls" + std::to_string(row), newEntity});
            }
            if (value[i] == 'H') {
                Entity newEntity = {
                    "lib/games/snake/files/snake/head-right.png",
                    "H",
                    "",
                    x,
                    y,
                    false,
                    false,
                    {255, 0, 0},
                    {0, 0, 0},
                };
                _entities.insert({"head", newEntity});
            }
            if (value[i] == 'T') {
                Entity newEntity = {
                    "lib/games/snake/files/snake/tail-right.png",
                    "T",
                    "",
                    x,
                    y,
                    false,
                    false,
                    {255, 0, 0},
                    {0, 0, 0},
                };
                _entities.insert({"tail", newEntity});
            }
            if (value[i] == 'S') {
                Entity newEntity = {
                    "lib/games/snake/files/snake/horizontal-body.png",
                    "S",
                    "",
                    x,
                    y,
                    false,
                    false,
                    {255, 0, 0},
                    {0, 0, 0},
                };
                _entities.insert({"horizontal-body", newEntity});
            }
            x += 1;
        }
        x = 0;
        y += 1;
        row++;
    }
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
        _gameStatus = FINISHED;
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
    print_grid(_grid);
    sleep(1);
}

std::map<std::string, IGameModule::Entity> Snake::getInfos()
{
    return _entities;
}

const std::string &Snake::getName() const
{
    return _name;
}

IGameModule::GAME_STATUS Snake::getGameStatus()
{
    return _gameStatus;
}

bool Snake::isGameOver()
{
    return false;
}

void Snake::generateGrid(int lenght)
{
    std::string val;
    val = std::string(lenght, '-');
    _grid.insert(_grid.end(), val);
    for (int i = 10; i != 0; i--) {
        val = std::string("-") + std::string(lenght - 2, ' ') + std::string("-");
        _grid.insert(_grid.end(), val);
    }
    val = std::string(lenght, '-');
    _grid.insert(_grid.end(), val);
    for (std::string val : _grid) {
        std::cout << val << std::endl;
    }
    _grid[5][50] = 'H';
    _grid[5][49] = 'S';
    _grid[5][48] = 'T';
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
