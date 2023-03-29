/*
**  ______   ______     ______     __    __     ______     __   __
** /\  == \ /\  __ \   /\  ___\   /\ "-./  \   /\  __ \   /\ "-.\ \
** \ \  _-/ \ \  __ \  \ \ \____  \ \ \-./\ \  \ \  __ \  \ \ \-.  \
**  \ \_\    \ \_\ \_\  \ \_____\  \ \_\ \ \_\  \ \_\ \_\  \ \_\\"\_\
**   \/_/     \/_/\/_/   \/_____/   \/_/  \/_/   \/_/\/_/   \/_/ \/_/
**
*/

#include "pacman.hpp"
#include <string>
#include <iostream>
#include <fstream>

void Pacman::pacmanPart()
{
    // TODO : 1 frame / 2 sprite
    int index = 0;
    if (getDirection() == DIRECTION::RIGHT)
        index = 1;
    if (getDirection() == DIRECTION::LEFT)
        index = 3;
    if (getDirection() == DIRECTION::UP)
        index = 5;
    if (getDirection() == DIRECTION::DOWN)
        index = 7;
    if (_second_sprite)
        index++;
    Entity newEntity = {
        index,
        "@",
        "",
        _pos_x,
        _pos_y + _decal_y,
        false,
        false,
        {255, 255, 0},
        {0, 0, 0},
    };
    setNewEntity("Pacman", newEntity);
}

int Pacman::chooseenemySprite (enemy_t enemy)
{
    if (!enemy.avlive) {
        if (enemy.direction == DIRECTION::RIGHT)
            return 48;
        else if (enemy.direction == DIRECTION::LEFT)
            return 49;
        else if (enemy.direction == DIRECTION::UP)
            return 50;
        return 51;
    }
    // begin at 9
    int index = 9;
    // TODO : when color is implemented
    if (enemy.color > 0)
        index += 8;
    if (enemy.color > 1)
        index += 8;
    if (enemy.color > 2)
        index += 8;
    if (enemy.direction == DIRECTION::RIGHT)
        index += 0;
    if (enemy.direction == DIRECTION::LEFT)
        index += 2;
    if (enemy.direction == DIRECTION::UP)
        index += 4;
    if (enemy.direction == DIRECTION::DOWN)
        index += 6;
    if (_invincible && enemy.weak) {
        index = 44;
        if (_invincible < 10 && _invincible % 2 == 0)
            index = 46;
    }
    if (_second_sprite)
        index++;
    return index;
}

void Pacman::enemyPart(enemy_t enemy, int i, int row)
{
    int index = chooseenemySprite(enemy);
    int red = 0;
    int green = 0;
    int blue = 0;
    if (enemy.color == 0) {
        red = 255;
        green = 0;
        blue = 0;
    } else if (enemy.color == 1) {
        red = 0;
        green = 255;
        blue = 0;
    } else if (enemy.color == 2) {
        red = 100;
        green = 100;
        blue = 255;
    } else if (enemy.color == 3) {
        red = 255;
        green = 255;
        blue = 0;
    }
    Entity newEntity = {
        index,
        "X",
        "",
        enemy.x,
        enemy.y + _decal_y,
        false,
        false,
        {red, green, blue},
        {0, 0, 0},
    };
    setNewEntity(std::to_string(i) + "enemy" + std::to_string(row), newEntity);
}

void Pacman::dataToEntity(void)
{
    float y = 0, x = 0;
    int row = 0;
    clearEntities();
    for (std::vector<int> value : getGrid()) {
        for (int i = 0; y <= getGrid().size() && i < getGrid()[y].size(); i++) {
            // # = wall
            // . = small food   (+1)
            // o = medium food  (+5)
            // O = big food     (+10)
            // @ = spawn
            // X = enemy
            if (value[i] == -2) { // walls
                Entity newEntity = {
                    0,
                    "#",
                    "",
                    x,
                    y + _decal_y,
                    false,
                    false,
                    {0, 0, 255},
                    {0, 0, 0},
                };
                setNewEntity(std::to_string(i) + "walls" + std::to_string(row), newEntity);
            } else if (value[i] == 2) { // small food
                Entity newEntity = {
                    41, // nothing
                    ".",
                    "",
                    x,
                    y + _decal_y,
                    false,
                    false,
                    {255, 255, 255},
                    {0, 0, 0},
                };
                setNewEntity(std::to_string(i) + "small food" + std::to_string(row), newEntity);
            } else if (value[i] == 3) { // medium food
                Entity newEntity = {
                    42, // nothing
                    "o",
                    "",
                    x,
                    y + _decal_y,
                    false,
                    false,
                    {255, 255, 255},
                    {0, 0, 0},
                };
                setNewEntity(std::to_string(i) + "medium food" + std::to_string(row), newEntity);
            } else if (value[i] == 4) { // big food
                Entity newEntity = {
                    43, // TODO: add big food
                    "O",
                    "",
                    x,
                    y + _decal_y,
                    false,
                    false,
                    {255, 255, 255},
                    {0, 0, 0},
                };
                setNewEntity(std::to_string(i) + "big food" + std::to_string(row), newEntity);
            } else if (value[i] == 6 || value[i] == 7) { // teleport
                Entity newEntity = {
                    -1, // TODO: add teleport
                    "",
                    "",
                    x,
                    y + _decal_y,
                    false,
                    false,
                    {0, 255, 0},
                    {0, 0, 0},
                };
                setNewEntity(std::to_string(i) + "teleport" + std::to_string(row), newEntity);
            }
            x += 1;
        }
        x = 0;
        y += 1;
        row++;
    }
    pacmanPart();
    for (int i = 0; i != _enemy.size(); i++) {
        enemyPart(_enemy[i], i, row++);
    }
    setNewEntity("gum", {
        -1,
        "Gum remain: " + std::to_string(_nbr_gums_remain),
        "",
        0,
        0,
        true,
        true,
        {255, 255, 255},
        {0, 0, 0},
    });
}
