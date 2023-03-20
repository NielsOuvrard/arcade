/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-arcade-adam.elaoumari [WSL : Ubuntu]
** File description:
** nibbler
*/

#include "nibbler.hpp"
#include <string>
#include <iostream>
#include <fstream>

std::vector<std::string> fileToArray (std::string filepath)
{
    std::ifstream inputFile(filepath);
    std::string line;
    std::vector<std::string> array;
    while (getline(inputFile, line)) {
        array.push_back(line);
    }
    inputFile.close();
    return array;
}

void Nibbler::getInfoSnake (std::vector<std::string> map)
{
    _size_snake = 0;
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] >= '0' && map[i][j] <= '9' && _size_snake < map[i][j] - '0') {
                _size_snake = map[i][j] - '0';
                _head_x = j;
                _head_y = i;
            }
        }
    }
}

Nibbler::Nibbler()
{
    std::vector<std::string> map = fileToArray("lib/games/nibbler/map1.txt");
    generateGrid(map);
    getInfoSnake(map);
    dataToEntity();
}

Nibbler::~Nibbler()
{
}

int Nibbler::chooseSprite (float x, float y, int value)
{
    if (!getGrid().size() || !getGrid()[y].size() || !getGrid()[y][x])
        return 0;
    if (getGrid()[y].size() > x && getGrid()[y][x + 1] > 0 && x > 0 && getGrid()[y][x - 1] > 0) // horizontal
        return 10;
    if (getGrid().size() > y && getGrid()[y + 1][x] > 0 && y > 0 && getGrid()[y - 1][x] > 0) // vertical
        return 1;
    if (value == _size_snake) { // head
        if (getDirection() == DIRECTION::DOWN) {
            return 6;
        } else if (getDirection() == DIRECTION::LEFT) {
            return 7;
        } else if (getDirection() == DIRECTION::RIGHT) {
            return 8;
        } else if (getDirection() == DIRECTION::UP) {
            return 9;
        }
    } else if (value == 1) { // tail
        if (getGrid().size() > y && getGrid()[y + 1][x] == 2) { // move down
            return 11;
        } else if (x > 0 && getGrid()[y][x - 1] == 2) { // move left
            return 12;
        } else if (getGrid()[y].size() > x && getGrid()[y][x + 1] == 2) { // move right
            return 13;
        } else if (y > 0 && getGrid()[y - 1][x] == 2) { // move up
            return 14;
        } else {
            return 10; // ?
        }
    } else {
        if (getGrid().size() > y && getGrid()[y + 1][x] > 0 && x > 0 && getGrid()[y][x - 1] > 0) // down left
            return 2;
        if (getGrid().size() > y && getGrid()[y + 1][x] > 0 && getGrid()[y].size() > x && getGrid()[y][x + 1] > 0) // down right
            return 3;
        if (y > 0 && getGrid()[y - 1][x] > 0 && x > 0 && getGrid()[y][x - 1] > 0) // up left
            return 4;
        if (y > 0 && getGrid()[y - 1][x] > 0 && getGrid()[y].size() > x && getGrid()[y][x + 1] > 0) // up right
            return 5;
    }
    return 10;
}

void Nibbler::snakePart(std::vector<int> value, float x, float y, int row, int i)
{
    std::vector<std::string> snake = {
        "A", "|", "\\", "/", "/", "\\", "M", "3", "E", "W", "=", "^", ">", "<", "v", "#", " "
    };

    int index_snake = chooseSprite(x, y, value[i]);
    Entity newEntity = {
        index_snake,
        snake[index_snake],
        "",
        x,
        y,
        false,
        false,
        {0, 255, 0},
        {0, 0, 0},
    };
    setNewEntity(std::to_string(i) + "snake" + std::to_string(row), newEntity);
}

void Nibbler::dataToEntity(void)
{
    float y = 0, x = 0;
    int row = 0;
    clearEntities();
    for (std::vector<int> value : getGrid()) {
        for (int i = 0; i < getGrid()[0].size(); i++) {
            // std::cout << value[i];
            if (value[i] == -2) { // walls
                Entity newEntity = {
                    15,
                    "#",
                    "",
                    x,
                    y,
                    false,
                    false,
                    {255, 255, 255},
                    {0, 0, 0},
                };
                setNewEntity(std::to_string(i) + "walls" + std::to_string(row), newEntity);
            } else if (value[i] == 0) { // spaces
                Entity newEntity = {
                    -1,
                    " ",
                    "",
                    x,
                    y,
                    false,
                    false,
                    {0, 0, 0},
                    {0, 0, 0},
                };
                setNewEntity(std::to_string(i) + "spaces" + std::to_string(row), newEntity);
            } else if (value[i] == -1) { // apple
                Entity newEntity = {
                    0,
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
            } else if (value[i] > 0) {
                snakePart(value, x, y, row, i);
            } else {
                // std::cout << "Error: " << value[i] << std::endl;
            }
            x += 1;
        }
        // std::cout << std::endl;
        x = 0;
        y += 1;
        row++;
    }
}

void Nibbler::moveHead(int x, int y, bool eat)
{
    setGridValue(_head_y += y, _head_x += x, _size_snake + 1);
    _size_snake += eat;
}

// turn = change _direction, and try to move
// how many apple
// victory condition
// fix game over

void Nibbler::move(void)
{
    if (getDirection() == UP && _head_y > 0 && getGrid()[_head_y - 1][_head_x] > -2) {
        if (getGrid()[_head_y - 1][_head_x] == -1) {
            moveHead(0, -1, true);
            return;
        } else if (getGrid()[_head_y - 1][_head_x] != 0) {
            setGameStatus(FINISHED);
            return;
        }
        moveHead(0, -1, false);
    } else if (getDirection() == DOWN && getGrid().size() > _head_y && getGrid()[_head_y + 1][_head_x] > -2) {
        if (getGrid()[_head_y + 1][_head_x] == -1) {
            moveHead(0, 1, true);
            return;
        } else if (getGrid()[_head_y + 1][_head_x] != 0) {
            setGameStatus(FINISHED);
            return;
        }
        moveHead(0, 1, false);
    } else if (getDirection() == LEFT && _head_x > 0 && getGrid()[_head_y][_head_x - 1] > -2) {
        if (getGrid()[_head_y][_head_x - 1] == -1) {
            moveHead(-1, 0, true);
            return;
        } else if (getGrid()[_head_y][_head_x - 1] != 0) {
            setGameStatus(FINISHED);
            return;
        }
        moveHead(-1, 0, false);
    } else if (getDirection() == RIGHT && getGrid()[_head_y].size() > _head_x && getGrid()[_head_y][_head_x + 1] > -2) {
        if (getGrid()[_head_y][_head_x + 1] == -1) {
            moveHead(1, 0, true);
            return;
        } else if (getGrid()[_head_y][_head_x + 1] != 0) {
            setGameStatus(FINISHED);
            return;
        }
        moveHead(1, 0, false);
    } else {
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
    if (key == "F1") {
        if (getCurrentRuntimeGraphicDisplay() == "lib/arcade_sfml.so") {
            setCurrentRuntimeGraphicDisplay("lib/arcade_sdl2.so");
        } else if (getCurrentRuntimeGraphicDisplay() == "lib/arcade_sdl2.so") {
            setCurrentRuntimeGraphicDisplay("lib/arcade_ncurses.so");
        } else {
            setCurrentRuntimeGraphicDisplay("lib/arcade_sfml.so");
        }
        return;
    }
    move();
    dataToEntity();
    if (key.empty())
        return;
    if (key == "close") {
        setGameStatus(FINISHED);
    }
}

extern "C" IGameModule *create(void) {
    return new Nibbler();
}

extern "C" void destroy(IGameModule* obj) {
    delete obj;
}

extern "C" std::string getType() {
    return "Game";
}

std::vector<std::string> Nibbler::getTextures() {
    std::vector<std::string> snake = {
        "lib/games/snake/files/snake/apple.png",
        "lib/games/snake/files/snake/body-vertical.png",
        "lib/games/snake/files/snake/curv-down-left.png",
        "lib/games/snake/files/snake/curv-down-right.png",
        "lib/games/snake/files/snake/curv-up-left.png",
        "lib/games/snake/files/snake/curv-up-right.png",
        "lib/games/snake/files/snake/head-down.png",
        "lib/games/snake/files/snake/head-left.png",
        "lib/games/snake/files/snake/head-right.png",
        "lib/games/snake/files/snake/head-up.png",
        "lib/games/snake/files/snake/horizontal-body.png",
        "lib/games/snake/files/snake/tail-down.png",
        "lib/games/snake/files/snake/tail-left.png",
        "lib/games/snake/files/snake/tail-right.png",
        "lib/games/snake/files/snake/tail-up.png",
        "lib/games/snake/files/snake/walls.png"
    };
    return snake;
}
