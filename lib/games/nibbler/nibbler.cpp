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
    for (std::vector<int> value : grid) {
        for (int i = 0; value[i]; i++) {
            if (value[i] == -2) {
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
            if (value[i] == 0) {
                Entity newEntity = {
                    "",
                    " ",
                    "",
                    x,
                    y,
                    false,
                    false,
                    {255, 0, 0},
                    {0, 0, 0},
                };
                entities.insert({std::to_string(i) + "spaces" + std::to_string(row), newEntity});
            }
            if (value[i] == -1) {
                Entity newEntity = {
                    "lib/games/snake/files/snake/apple.png",
                    "A",
                    "",
                    x,
                    y,
                    false,
                    false,
                    {255, 0, 0},
                    {0, 0, 0},
                };
                entities.insert({std::to_string(i) + "apples" + std::to_string(row), newEntity});
            }
            if (value[i] > 0) {
                Entity newEntity = {
                    "lib/games/snake/files/snake/body-vertical.png",
                    "S",
                    "",
                    x,
                    y,
                    false,
                    false,
                    {255, 0, 0},
                    {0, 0, 0},
                };
                entities.insert({std::to_string(i) + "snake" + std::to_string(row), newEntity});
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
    if (_direction == RIGHT) {

    }
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
    std::vector<int> val2(lenght, -2);
    grid.insert(grid.end(), val2);
    for (int i = 10; i != 0; i--) {
        std::vector<int> val;
        val.insert(val.end(), -2);
        val.resize(val.size() + lenght - 2, 0);
        val.insert(val.end(), -2);
        grid.insert(grid.end(), val);
    }
    grid.insert(grid.end(), val2);
    std::cout << "voici la map" << std::endl;
    for (std::vector<int> value : grid) {
        for (int i = 0; value[i]; i++) {
            if (value[i] == 0)
                std::cout << " ";
            if (value[i] == -2)
                std::cout << "-";
        }
        std::cout << std::endl;
    }
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