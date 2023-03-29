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

void Pacman::resetGame(void)
{
    clearGrid();
    _isAlive = true;
    _isMoving = false;
    _score = 0;
    _invincible = 0;
    _enemy.clear();
    std::vector<std::string> map = fileToArray("lib/games/pacman/map" + std::to_string(_level) + ".txt");
    generateGrid(map, true);
    fillGumsRemain();
    getInfoMap(map);
    dataToEntity();
    setDirection(DIRECTION::RIGHT);
    _next_direction = RIGHT;
}

extern "C" IGameModule *create(void) {
    return new Pacman();
}

extern "C" std::string getType() {
    return "Game";
}

std::vector<std::string> Pacman::getTextures() {
    std::vector<std::string> files_path = {
        "lib/games/Pacman/files/wall.png",
        // lib/games/pacman/files/player-down-1.png
        "lib/games/Pacman/files/player-right-1.png",
        "lib/games/Pacman/files/player-right-2.png",
        "lib/games/Pacman/files/player-left-1.png",
        "lib/games/Pacman/files/player-left-2.png",
        "lib/games/Pacman/files/player-up-1.png",
        "lib/games/Pacman/files/player-up-2.png",
        "lib/games/Pacman/files/player-down-1.png",
        "lib/games/Pacman/files/player-down-2.png",
        // lib/games/pacman/files/ghost-blue-1.png
        "lib/games/Pacman/files/ghost-blue-1.png", // right
        "lib/games/Pacman/files/ghost-blue-2.png",
        "lib/games/Pacman/files/ghost-blue-3.png", // left
        "lib/games/Pacman/files/ghost-blue-4.png",
        "lib/games/Pacman/files/ghost-blue-5.png", // up
        "lib/games/Pacman/files/ghost-blue-6.png",
        "lib/games/Pacman/files/ghost-blue-7.png", // down
        "lib/games/Pacman/files/ghost-blue-8.png",
        // lib/games/pacman/files/ghost-pink-1.png
        "lib/games/Pacman/files/ghost-pink-1.png", // right
        "lib/games/Pacman/files/ghost-pink-2.png",
        "lib/games/Pacman/files/ghost-pink-3.png", // left
        "lib/games/Pacman/files/ghost-pink-4.png",
        "lib/games/Pacman/files/ghost-pink-5.png", // up
        "lib/games/Pacman/files/ghost-pink-6.png",
        "lib/games/Pacman/files/ghost-pink-7.png", // down
        "lib/games/Pacman/files/ghost-pink-8.png",
        // lib/games/pacman/files/ghost-orange-1.png
        "lib/games/Pacman/files/ghost-orange-1.png", // right
        "lib/games/Pacman/files/ghost-orange-2.png",
        "lib/games/Pacman/files/ghost-orange-3.png", // left
        "lib/games/Pacman/files/ghost-orange-4.png",
        "lib/games/Pacman/files/ghost-orange-5.png", // up
        "lib/games/Pacman/files/ghost-orange-6.png",
        "lib/games/Pacman/files/ghost-orange-7.png", // down
        "lib/games/Pacman/files/ghost-orange-8.png",
        // lib/games/pacman/files/ghost-red-1.png
        "lib/games/Pacman/files/ghost-red-1.png", // right
        "lib/games/Pacman/files/ghost-red-2.png",
        "lib/games/Pacman/files/ghost-red-3.png", // left
        "lib/games/Pacman/files/ghost-red-4.png",
        "lib/games/Pacman/files/ghost-red-5.png", // up
        "lib/games/Pacman/files/ghost-red-6.png",
        "lib/games/Pacman/files/ghost-red-7.png", // down
        "lib/games/Pacman/files/ghost-red-8.png",
        // food
        "lib/games/Pacman/files/small-food.png",
        "lib/games/Pacman/files/medium-food.png",
        "lib/games/Pacman/files/big-food.png",
        // ghost-weak-9 = 44
        "lib/games/Pacman/files/ghost-weak-9.png",
        "lib/games/Pacman/files/ghost-weak-10.png",
        "lib/games/Pacman/files/ghost-weak-11.png",
        "lib/games/Pacman/files/ghost-weak-12.png",
    };
    return files_path;
}
