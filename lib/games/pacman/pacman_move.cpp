/*
**  ______   ______     ______     __    __     ______     __   __
** /\  == \ /\  __ \   /\  ___\   /\ "-./  \   /\  __ \   /\ "-.\ \
** \ \  _-/ \ \  __ \  \ \ \____  \ \ \-./\ \  \ \  __ \  \ \ \-.  \
**  \ \_\    \ \_\ \_\  \ \_____\  \ \_\ \ \_\  \ \_\ \_\  \ \_\\"\_\
**   \/_/     \/_/\/_/   \/_____/   \/_/  \/_/   \/_/\/_/   \/_/ \/_/
**
*/

#include "pacman.hpp"
#include "pathfinding.hpp"
#include <string>
#include <iostream>
#include <fstream>

bool Pacman::eventAfterMoving(int x, int y)
{
    if (getGrid()[_pos_y + y][_pos_x + x] == 2) {
        _score += 1;
        _nbr_gums_remain--;
    } else if (getGrid()[_pos_y + y][_pos_x + x] == 3) {
        _nbr_gums_remain--;
        _score += 5;
    } else if (getGrid()[_pos_y + y][_pos_x + x] == 4) {
        _nbr_gums_remain--;
        _score += 10;
        _invincible += 30; // TODO 10 secondes ?
    }
    if (!_nbr_gums_remain) {
        _level++;
        resetGame();
    }
    return 0;
}

t_myopen nextPositionGhost(t_myopen ghost, t_myopen target, std::vector<std::vector<int>> _grid);

void Pacman::enemyMove(void)
{
    // blue pink orange red
    for (int i = 0; i != _enemy.size() / 2; i++) {
        if (_enemy[i].avlive == true) {
            t_myopen ghost;
            t_myopen target;
            ghost.x = _enemy[i].x;
            ghost.y = _enemy[i].y;
            target.x = _pos_x;
            target.y = _pos_y;
            t_myopen next = nextPositionGhost(ghost, target, getGrid());
            if (next.x != -1 && next.y != -1) {
                _enemy[i].x = next.x;
                _enemy[i].y = next.y;
            }
        }
    }
}

bool Pacman::isValidPosition(int x, int y) const
{
    return x >= 0 && y >= 0 && y < getGrid().size() && x < getGrid()[y].size() && getGrid()[y][x] > -2;
}

void Pacman::move(void)
{
    if (_next_direction == UP && isValidPosition(_pos_x, _pos_y - 1)) {
        setDirection(UP);
    } else if (_next_direction == DOWN && isValidPosition(_pos_x, _pos_y + 1)) {
        setDirection(DOWN);
    } else if (_next_direction == LEFT && isValidPosition(_pos_x - 1, _pos_y)) {
        setDirection(LEFT);
    } else if (_next_direction == RIGHT && isValidPosition(_pos_x + 1, _pos_y)) {
        setDirection(RIGHT);
    }
    if (getDirection() == UP && isValidPosition(_pos_x, _pos_y - 1)) {
        if (_pos_y - 1 == 0) {
            _pos_y = getGrid().size() - 1;
            return;
        }
        eventAfterMoving(0, -1);
        setGridValue(--_pos_y, _pos_x, 0);
    } else if (getDirection() == DOWN && isValidPosition(_pos_x, _pos_y + 1)) {
        if (_pos_y + 1 == getGrid().size() - 1) {
            _pos_y = 0;
            return;
        }
        eventAfterMoving(0, 1);
        setGridValue(++_pos_y, _pos_x, 0);
    } else if (getDirection() == LEFT && isValidPosition(_pos_x - 1, _pos_y)) {
        if (_pos_x - 1 == 0) {
            _pos_x = getGrid()[_pos_y].size() - 1;
            return;
        }
        eventAfterMoving(-1, 0);
        setGridValue(_pos_y, --_pos_x, 0);
    } else if (getDirection() == RIGHT && isValidPosition(_pos_x + 1, _pos_y)) {
        if (_pos_x + 1 == getGrid()[_pos_y].size() - 1) {
            _pos_x = 0;
            return;
        }
        eventAfterMoving(1, 0);
        setGridValue(_pos_y, ++_pos_x, 0);
    } else {
        _isMoving = false;
    }
}
