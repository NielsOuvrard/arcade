/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-arcade-adam.elaoumari
** File description:
** snake
*/

#include "snake.hpp"

Snake::Snake()
{
    float x = 600, y = 3;
    Entity gameEntity  = {
        "lib/games/snake/files/snake/head-right.png",
        "",
        "E9967A",
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
        "",
        "E9967A",
        x,
        y,
        false,
        false,
        0,
        0,
        0
    };
    _entities.insert({"snake-tail", gameEntity});
    _gameObject.push_back(_entities);
}

Snake::~Snake()
{
}

void Snake::update(std::string key)
{
    if (key.empty()) {
        if (_direction == DIRECTION::RIGHT) {
            for (auto &gameObject : _gameObject) {
                for (auto &entity : gameObject) {
                    entity.second.x += 2 * _speed;
                }
            }
        }
        else if (_direction == DIRECTION::LEFT) {
            for (auto &gameObject : _gameObject) {
                for (auto &entity : gameObject) {
                    entity.second.x -= 2 * _speed;
                }
            }
        }
        else if (_direction == DIRECTION::UP) {
            for (auto &gameObject : _gameObject) {
                for (auto &entity : gameObject) {
                    entity.second.y -= 0.02 * _speed;
                }
            }
        }
        else if (_direction == DIRECTION::DOWN) {
            for (auto &gameObject : _gameObject) {
                for (auto &entity : gameObject) {
                    entity.second.y += 0.02 * _speed;
                }
            }
        }
    }
    if (key == "close") {
        _gameStatus = FINISHED;
    }
    if (key == "UpArrow") {
        _entities["snake-head"].y -= 0.03;
        _direction = DIRECTION::UP;
    }
    if (key == "DownArrow") {
        _entities["snake-head"].y += 0.03;
        _direction = DIRECTION::DOWN;
    }
    if (key == "LeftArrow") {
        _entities["snake-head"].x -= 5;
        _direction = DIRECTION::LEFT;
    }
    if (key == "RightArrow") {
        _entities["snake-head"].x += 5;
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
