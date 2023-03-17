/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-arcade-adam.elaoumari [WSL : Ubuntu]
** File description:
** nibbler
*/

#include "nibbler.hpp"

Nibbler::Nibbler()
{
    generateGrid(100);
    float y = 0, x = 0;
    int row = 0;
    for (std::string value : grid) {
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
                entities.insert({std::to_string(i) + "walls" + std::to_string(row), newEntity});
            }
            x += 1;
        }
        x = 0;
        y += 1;
        row++;
    }
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

void Nibbler::generateGrid(int lenght)
{
    std::string val;
    val = std::string(lenght, '-');
    grid.insert(grid.end(), val);
    for (int i = 10; i != 0; i--) {
        val = std::string("-") + std::string(lenght - 2, ' ') + std::string("-");
        grid.insert(grid.end(), val);
    }
    val = std::string(lenght, '-');
    grid.insert(grid.end(), val);
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