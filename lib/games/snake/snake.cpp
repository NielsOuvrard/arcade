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
            x += 1;
        }
        x = 0;
        y += 1;
        row++;
    }
    x = 600, y = 3;
    Entity gameEntity  = {
        "lib/games/snake/files/snake/head-right.png",
        "H",
        "",
        x,
        y,
        false,
        false,
        0,
        0,
        0
    };
    _entities.insert({"snake-head", gameEntity});
    x = 536; y = 3;
    gameEntity  = {
        "lib/games/snake/files/snake/tail-right.png",
        "T",
        "",
        x,
        y,
        false,
        false,
        0,
        0,
        0
    };
    _entities.insert({"snake-tail", gameEntity});
}

Snake::~Snake()
{
}

void Snake::update(std::string key)
{
    if (key.empty()) {
        if (_direction == DIRECTION::RIGHT) {
            _entities["snake-head"].x += 0.03;
            _entities["snake-tail"].x += 0.03;
        }
        else if (_direction == DIRECTION::LEFT) {
            _entities["snake-head"].x -= 0.03;
            _entities["snake-tail"].x -= 0.03;
        }
        else if (_direction == DIRECTION::UP) {
            _entities["snake-head"].y -= 0.03;
            _entities["snake-tail"].y -= 0.03;
        }
        else if (_direction == DIRECTION::DOWN) {
            _entities["snake-head"].y += 0.03;
            _entities["snake-tail"].y += 0.03;
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
