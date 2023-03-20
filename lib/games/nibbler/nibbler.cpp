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
    dataToEntity();
    generateApple();
}

Nibbler::~Nibbler()
{
}

void Nibbler::generateApple(void)
{
    std::cout << "generate apple" << std::endl;
    int x = rand() % 100;
    int y = rand() % 10;
    std::cout << "x: " << x << " y: " << y << std::endl;
    if (getGrid()[y][x] == 0) {
        std::cout << "apple generated in " << x << " " << y << std::endl;
        setGridValue(y, x, -1);
    } else {
        generateApple();
    }
}

void Nibbler::dataToEntity(void)
{
    float y = 0, x = 0;
    int row = 0;
    clearEntities();
    for (std::vector<int> value : getGrid()) {
        for (int i = 0; i != 100; i++) {
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
                setNewEntity(std::to_string(i) + "walls" + std::to_string(row), newEntity);
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
                setNewEntity(std::to_string(i) + "spaces" + std::to_string(row), newEntity);
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
                setNewEntity(std::to_string(i) + "apples" + std::to_string(row), newEntity);
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
                setNewEntity(std::to_string(i) + "snake" + std::to_string(row), newEntity);
            }
            x += 1;
        }
        x = 0;
        y += 1;
        row++;
    }
}

void Nibbler::move(void)
{
    int x_head, y_head, head_value = 0;
    for (int i = 0; i != getGrid().size(); i++) {
        for (int j = 0; j != getGrid()[i].size(); j++) {
            if (getGrid()[i][j] > head_value) {
                head_value = getGrid()[i][j];
                x_head = j;
                y_head = i;
            }
        }
    }
    if (head_value == 0)
        return;
    if (getDirection() == UP && y_head > 0 && getGrid()[y_head - 1][x_head] > -2) {
        if (getGrid()[y_head - 1][x_head] == -1) {
            setGridValue(y_head - 1, x_head, head_value + 1);
            generateApple();
            return;
        }
        setGridValue(y_head - 1, x_head, head_value + 1);
    } else if (getDirection() == DOWN && getGrid().size() > y_head && getGrid()[y_head + 1][x_head] > -2) {
        if (getGrid()[y_head + 1][x_head] == -1) {
            setGridValue(y_head + 1, x_head, head_value + 1);
            generateApple();
            return;
        }
        setGridValue(y_head + 1, x_head, head_value + 1);
    } else if (getDirection() == LEFT && x_head > 0 && getGrid()[y_head][x_head - 1] > -2) {
        if (getGrid()[y_head][x_head - 1] == -1) {
            setGridValue(y_head, x_head - 1, head_value + 1);
            generateApple();
            return;
        }
        setGridValue(y_head, x_head - 1, head_value + 1);
    } else if (getDirection() == RIGHT && getGrid()[y_head].size() > x_head && getGrid()[y_head][x_head + 1] > -2) {
        if (getGrid()[y_head][x_head + 1] == -1) {
            setGridValue(y_head, x_head + 1, head_value + 1);
            generateApple();
            return;
        }
        setGridValue(y_head, x_head + 1, head_value + 1);
    } else {
        setGameStatus(FINISHED);
        return;
    }
    for (int i = 0; i != getGrid().size(); i++) {
        for (int j = 0; j != getGrid()[i].size(); j++) {
            if (getGrid()[i][j] > 0) {
                setGridValue(i, j, getGrid()[i][j] - 1);
            }
        }
    }
}

void Nibbler::update(std::string key)
{
    if (key == "LeftArrow" && getDirection() != RIGHT)
        setDirection(LEFT);
    if (key == "RightArrow" && getDirection() != LEFT)
        setDirection(RIGHT);
    if (key == "UpArrow" && getDirection() != DOWN)
        setDirection(UP);
    if (key == "DownArrow" && getDirection() != UP)
        setDirection(DOWN);
    move();
    dataToEntity();
    if (key.empty())
        return;
    if (key == "close") {
        setGameStatus(FINISHED);
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
