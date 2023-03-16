/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-arcade-adam.elaoumari
** File description:
** snake
*/

#include "snake.hpp"

Snake::Snake()
{
}

Snake::~Snake()
{
}

void Snake::update(std::string key)
{
    return;
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

std::string Snake::getEvent()
{
    return _event;
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
