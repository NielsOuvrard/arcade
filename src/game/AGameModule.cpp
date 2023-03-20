/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-arcade-adam.elaoumari
** File description:
** AGameModule
*/

#include "AGameModule.hpp"

AGameModule::AGameModule()
{
}

AGameModule::~AGameModule()
{
}

void AGameModule::startGame() {
    _status = IN_GAME;
};

bool AGameModule::isGameOver()
{
    if (_status == FINISHED)
        return true;
    return false;
}

std::string AGameModule::getCurrentRuntimeGraphicDisplay() const
{
    return _currentRuntimeGraphicDisplay;
}

void AGameModule::setCurrentRuntimeGraphicDisplay(std::string currentRuntimeGraphicDisplay)
{
    _currentRuntimeGraphicDisplay = currentRuntimeGraphicDisplay;
}

AGameModule::GAME_STATUS AGameModule::getGameStatus() const
{
    return _status;
}

void AGameModule::setGameStatus(GAME_STATUS status)
{
    _status = status;
}

void AGameModule::setNewEntity(std::string name, Entity entity)
{
    _entities.insert({name, entity});
}

void AGameModule::clearEntities()
{
    _entities.clear();
}

std::map<std::string, AGameModule::Entity> AGameModule::getInfos() const
{
    return _entities;
}

void AGameModule::generateGrid(int lenght)
{
    std::vector<int> val2(lenght, -2);
    _grid.insert(_grid.end(), val2);
    for (int i = 10; i != 0; i--) {
        std::vector<int> val;
        val.insert(val.end(), -2);
        val.resize(val.size() + lenght - 2, 0);
        val.insert(val.end(), -2);
        _grid.insert(_grid.end(), val);
    }
    _grid.insert(_grid.end(), val2);
    _grid[3][1] = 1;
    _grid[3][2] = 2;
    _grid[3][3] = 3;
    _grid[3][4] = 4; // ? shure ? only for snake
}

std::vector<std::vector<int>> AGameModule::getGrid() const
{
    return _grid;
}

void AGameModule::setGridValue(int y, int x, int value)
{
    _grid[y][x] = value;
}

AGameModule::DIRECTION AGameModule::getDirection() const
{
    return _direction;
}

void AGameModule::setDirection(AGameModule::DIRECTION direction)
{
    _direction = direction;
}

AGameModule::Entity &AGameModule::getEntity(std::string name) const
{
    return _entities.at(name);
}
