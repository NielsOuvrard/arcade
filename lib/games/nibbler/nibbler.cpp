/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-arcade-adam.elaoumari [WSL : Ubuntu]
** File description:
** nibbler
*/

#include "nibbler.hpp"

Nibbler::Nibbler()
{

}

Nibbler::~Nibbler()
{

}

void Nibbler::startGame()
{

}

void Nibbler::update(std::string key)
{
    if (key.empty())
        return;
    if (key == "close") {
        status = FINISHED;
    }
}

bool Nibbler::isGameOver()
{
    return (getGameStatus() == FINISHED);
}

extern "C" IGameModule *create(void)
{
    return new Nibbler();
}

extern "C" void destroy(IGameModule* obj) {
    delete obj;
}

extern "C" std::string getType() {
    return "Game";
}