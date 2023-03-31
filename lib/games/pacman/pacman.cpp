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

std::vector<std::string> fileToArray (std::string filepath)
{
    std::ifstream inputFile(filepath);
    if (!inputFile.is_open()) {
        std::cerr << "Error: file " << filepath << " not found" << std::endl;
        exit(84);
    }
    std::string line;
    std::vector<std::string> array;
    while (getline(inputFile, line)) {
        array.push_back(line);
    }
    inputFile.close();
    return array;
}

void Pacman::getInfoMap (std::vector<std::string> map)
{
    int color_enemy = 0;
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == '@') {
                _pos_x = j;
                _pos_y = i;
            } else if (map[i][j] == 'X') {
                enemy_t enemy;
                enemy.color = (color_enemy % 4);
                enemy.x = j;
                enemy.y = i;
                enemy.avlive = true;
                enemy.direction = RIGHT;
                enemy.weak = false;
                _enemy.push_back(enemy);
                color_enemy++;
            } else if (map[i][j] == 's') {
                _pos_enemy_spawn.x = j;
                _pos_enemy_spawn.y = i;
            } else if (map[i][j] == '@') {
                _pos_pacman_spawn.x = j;
                _pos_pacman_spawn.y = i;
            }
        }
    }
}

void writeAtEnd(std::string str)
{
    std::ofstream file;
    file.open("file.txt", std::ios::app);
    file << str << std::endl;
    file.close();
}

void Pacman::fillGumsRemain()
{
    _nbr_gums_remain = 0;
    for (int i = 0; i < getGrid().size(); i++)
        for (int j = 0; j < getGrid()[i].size(); j++)
            if (getGrid()[i][j] >= 2 && getGrid()[i][j] <= 4)
                    _nbr_gums_remain++;
}

Pacman::Pacman()
{
    std::vector<std::string> map = fileToArray("lib/games/pacman/map" + std::to_string(_level) + ".txt");
    // compt _nmbr_gums_remain
    // # = wall
    // . = small food   (+1)
    // o = medium food  (+5)
    // 0 = big food     (+10)
    // @ = spawn
    // X = enemy
    generateGrid(map, true);
    fillGumsRemain();
    getInfoMap(map);
    dataToEntity();
    setDirection(DIRECTION::RIGHT);
}

Pacman::~Pacman()
{
}

// check if pacman touch enemy
int Pacman::checkIfPacmanTouchenemy(void)
{
    for (int i = 0; i != _enemy.size(); i++) {
        if (_pos_x == _enemy[i].x && _pos_y == _enemy[i].y) {
            if (_invincible && _enemy[i].weak) {
                _enemy[i].avlive = false;
                _score += 100;
                return 0;
            } else {
                _isAlive = false;
                return 1;
            }
        }
    }
    return 0;
}

void Pacman::update(std::string key)
{
    if (key == "LeftArrow") {
        _next_direction = LEFT;
        _isMoving = true;
    } else if (key == "RightArrow") {
        _next_direction = RIGHT;
        _isMoving = true;
    } else if (key == "UpArrow") {
        _next_direction = UP;
        _isMoving = true;
    } else if (key == "DownArrow") {
        _next_direction = DOWN;
        _isMoving = true;
    }
    if (getTimeElapsed(start) < std::chrono::milliseconds(200)) {
        return;
    } else {
        _second_sprite = !_second_sprite;
        if (_invincible)
            _invincible -= 1;
        setChronoValue(std::chrono::high_resolution_clock::now());
    }
    if (!_invincible) {
        for (int i = 0; i != _enemy.size(); i++) {
            _enemy[i].weak = false;
        }
    }
    // check if pacman touch enemy
    if (checkIfPacmanTouchenemy())
        resetGame();
    if (_isMoving)
        move();
    if (checkIfPacmanTouchenemy())
        resetGame();
    if (_delay_ghost-- < 0)
        enemyMove();
    dataToEntity();
    if (key.empty())
        return;
    if (key == "close") {
        setGameStatus(FINISHED);
    }
}
