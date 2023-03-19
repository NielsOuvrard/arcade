/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-arcade-adam.elaoumari [WSL : Ubuntu]
** File description:
** nibbler
*/

#include "nibbler.hpp"

void Nibbler::generateApple(void)
{
    std::cout << "generate apple" << std::endl;
    int x = rand() % 100;
    int y = rand() % 10;
    std::cout << "x: " << x << " y: " << y << std::endl;
    if (grid[y][x] == 0) {
        std::cout << "apple generated in " << x << " " << y << std::endl;
        grid[y][x] = -1;
    } else {
        generateApple();
    }
}

void Nibbler::dataToEntity(void)
{
    float y = 0, x = 0;
    int row = 0;
    entities.clear();
    for (std::vector<int> value : grid) {
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
                // std::cout << newEntity.y << std::endl;
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


Nibbler::Nibbler()
{
    generateGrid(100);
    dataToEntity();
}

Nibbler::~Nibbler()
{

}

void Nibbler::startGame()
{

}

void Nibbler::move(void)
{
    // std::cout << "move" << std::endl;
    int x_head, y_head, head_value = 0;
    for (int i = 0; i != grid.size(); i++) {
        for (int j = 0; j != grid[i].size(); j++) {
            if (grid[i][j] > head_value) {
                head_value = grid[i][j];
                x_head = j;
                y_head = i;
            }
        }
    }
    if (head_value == 0)
        return;
    // std::cout << "x_head: " << x_head << " y_head: " << y_head << std::endl;

    if (_direction == UP && y_head > 0 && grid[y_head - 1][x_head] > -2) {
        if (grid[y_head - 1][x_head] == -1) {
            grid[y_head - 1][x_head] = head_value + 1;
            generateApple();
            return;
        }
        grid[y_head - 1][x_head] = head_value + 1;
    } else if (_direction == DOWN && grid.size() > y_head && grid[y_head + 1][x_head] > -2) {
        if (grid[y_head + 1][x_head] == -1) {
            grid[y_head + 1][x_head] = head_value + 1;
            generateApple();
            return;
        }
        grid[y_head + 1][x_head] = head_value + 1;
    } else if (_direction == LEFT && x_head > 0 && grid[y_head][x_head - 1] > -2) {
        if (grid[y_head][x_head - 1] == -1) {
            grid[y_head][x_head - 1] = head_value + 1;
            generateApple();
            return;
        }
        grid[y_head][x_head - 1] = head_value + 1;
    } else if (_direction == RIGHT && grid[y_head].size() > x_head && grid[y_head][x_head + 1] > -2) {
        if (grid[y_head][x_head + 1] == -1) {
            grid[y_head][x_head + 1] = head_value + 1;
            generateApple();
            return;
        }
        grid[y_head][x_head + 1] = head_value + 1;
    } else {
        status = FINISHED;
        return;
    }

    for (int i = 0; i != grid.size(); i++) {
        for (int j = 0; j != grid[i].size(); j++) {
            if (grid[i][j] > 0) {
                grid[i][j] -= 1;
            }
        }
    }
}

void Nibbler::update(std::string key)
{
    // std::cout << "update" << std::endl;
    if (key == "LeftArrow" && _direction != RIGHT)
        _direction = LEFT;
    if (key == "RightArrow" && _direction != LEFT)
        _direction = RIGHT;
    if (key == "UpArrow" && _direction != DOWN)
        _direction = UP;
    if (key == "DownArrow" && _direction != UP)
        _direction = DOWN;

    // std::cout << "direction: " << _direction << std::endl;

    move();
    dataToEntity();
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
    grid[1][1] = 1;
    grid[1][2] = 2;
    grid[1][3] = 3;
    grid[1][4] = 4;
    generateApple();
    // grid[2][4] = -1;
    // std::cout << "voici la map" << std::endl;
    // for (std::vector<int> value : grid) {
    //     for (int i = 0; value[i]; i++) {
    //         if (value[i] == 0)
    //             std::cout << " ";
    //         if (value[i] == -2)
    //             std::cout << "-";
    //     }
    //     std::cout << std::endl;
    // }
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