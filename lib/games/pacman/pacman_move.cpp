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
        _invincible += 50; // 10 sec
        for (int i = 0; i < _enemy.size(); i++)
            _enemy[i].weak = true;
    }
    if (!_nbr_gums_remain) {
        _level++;
        resetGame();
    }
    return 0;
}

t_myopen nextPositionGhost(t_myopen ghost, t_myopen target, std::vector<std::vector<int>> _grid);

t_myopen Pacman::nextPositionPacman(void)
{
    int x = 0, y = 0;
    if (getDirection() == UP) {
        while (isValidPosition(_pos_x, _pos_y + y))
            y--;
        y++;
    } else if (getDirection() == DOWN) {
        while (isValidPosition(_pos_x, _pos_y + y))
            y++;
        y--;
    } else if (getDirection() == LEFT) {
        while (isValidPosition(_pos_x + x, _pos_y))
            x--;
        x++;
    } else if (getDirection() == RIGHT) {
        while (isValidPosition(_pos_x + x, _pos_y))
            x++;
        x--;
    }
    t_myopen next;
    next.x = _pos_x + x;
    next.y = _pos_y + y;
    return next;
}


bool Pacman::isValidPositionEnnemy(int x, int y) const
{
    return x >= 0 && y >= 0 && y < getGrid().size() && x < getGrid()[y].size() && getGrid()[y][x] != -2;
}

void Pacman::enemyMoveRandow(int enemy)
{
    if (_enemy[enemy].direction == RIGHT && isValidPositionEnnemy(_enemy[enemy].x + 1, _enemy[enemy].y)) {
        if (isValidPositionEnnemy(_enemy[enemy].x, _enemy[enemy].y + 1) && rand() % 2) {
            _enemy[enemy].direction = DOWN;
        } else if (isValidPositionEnnemy(_enemy[enemy].x, _enemy[enemy].y - 1) && rand() % 2) {
            _enemy[enemy].direction = UP;
        }
    } else if (_enemy[enemy].direction == LEFT && isValidPositionEnnemy(_enemy[enemy].x - 1, _enemy[enemy].y)) {
        if (isValidPositionEnnemy(_enemy[enemy].x, _enemy[enemy].y + 1) && rand() % 2) {
            _enemy[enemy].direction = DOWN;
        } else if (isValidPositionEnnemy(_enemy[enemy].x, _enemy[enemy].y - 1) && rand() % 2) {
            _enemy[enemy].direction = UP;
        }
    } else if (_enemy[enemy].direction == UP && isValidPositionEnnemy(_enemy[enemy].x, _enemy[enemy].y - 1)) {
        if (isValidPositionEnnemy(_enemy[enemy].x + 1, _enemy[enemy].y) && rand() % 2) {
            _enemy[enemy].direction = RIGHT;
        } else if (isValidPositionEnnemy(_enemy[enemy].x - 1, _enemy[enemy].y) && rand() % 2) {
            _enemy[enemy].direction = LEFT;
        }
    } else if (_enemy[enemy].direction == DOWN && isValidPositionEnnemy(_enemy[enemy].x, _enemy[enemy].y + 1)) {
        if (isValidPositionEnnemy(_enemy[enemy].x + 1, _enemy[enemy].y) && rand() % 2) {
            _enemy[enemy].direction = RIGHT;
        } else if (isValidPositionEnnemy(_enemy[enemy].x - 1, _enemy[enemy].y) && rand() % 2) {
            _enemy[enemy].direction = LEFT;
        }
    } else {
        if (_enemy[enemy].direction == RIGHT || _enemy[enemy].direction == LEFT) {
            if (!isValidPositionEnnemy(_enemy[enemy].x, _enemy[enemy].y + 1) && !isValidPositionEnnemy(_enemy[enemy].x, _enemy[enemy].y - 1)) {
                if (_enemy[enemy].direction == RIGHT) {
                    _enemy[enemy].direction = LEFT;
                } else {
                    _enemy[enemy].direction = RIGHT;
                }
            } else if (!isValidPositionEnnemy(_enemy[enemy].x, _enemy[enemy].y + 1)) {
                _enemy[enemy].direction = UP;
            } else if (!isValidPositionEnnemy(_enemy[enemy].x, _enemy[enemy].y - 1)) {
                _enemy[enemy].direction = DOWN;
            } else {
                if (rand() % 2) {
                    _enemy[enemy].direction = UP;
                } else {
                    _enemy[enemy].direction = DOWN;
                }
            }
        } else if (_enemy[enemy].direction == UP || _enemy[enemy].direction == DOWN) {
            if (!isValidPositionEnnemy(_enemy[enemy].x + 1, _enemy[enemy].y) && !isValidPositionEnnemy(_enemy[enemy].x - 1, _enemy[enemy].y)) {
                if (_enemy[enemy].direction == UP) {
                    _enemy[enemy].direction = DOWN;
                } else {
                    _enemy[enemy].direction = UP;
                }
            } else if (!isValidPositionEnnemy(_enemy[enemy].x + 1, _enemy[enemy].y)) {
                _enemy[enemy].direction = LEFT;
            } else if (!isValidPositionEnnemy(_enemy[enemy].x - 1, _enemy[enemy].y)) {
                _enemy[enemy].direction = RIGHT;
            } else {
                if (rand() % 2) {
                    _enemy[enemy].direction = LEFT;
                } else {
                    _enemy[enemy].direction = RIGHT;
                }
            }
        }
    }
    if (_enemy[enemy].direction == RIGHT)
        _enemy[enemy].x++;
    else if (_enemy[enemy].direction == LEFT)
        _enemy[enemy].x--;
    else if (_enemy[enemy].direction == UP)
        _enemy[enemy].y--;
    else if (_enemy[enemy].direction == DOWN)
        _enemy[enemy].y++;
}

void Pacman::enemyReturnToHome(int enemy)
{
    // TODO _enemy[enemy].pos
    t_myopen ghost;
    t_myopen target = _pos_enemy_spawn;
    ghost.x = _enemy[enemy].x;
    ghost.y = _enemy[enemy].y;
    t_myopen next = nextPositionGhost(ghost, target, getGrid());
    // TODO check direction, and hadle error
    if (next.x != -1 && next.y != -1) {
        if (next.x > _enemy[enemy].x)
            _enemy[enemy].direction = RIGHT;
        else if (next.x < _enemy[enemy].x)
            _enemy[enemy].direction = LEFT;
        else if (next.y > _enemy[enemy].y)
            _enemy[enemy].direction = DOWN;
        else if (next.y < _enemy[enemy].y)
            _enemy[enemy].direction = UP;
        _enemy[enemy].x = next.x;
        _enemy[enemy].y = next.y;
    }
    if (_enemy[enemy].x == _pos_enemy_spawn.x && _enemy[enemy].y == _pos_enemy_spawn.y) {
        _enemy[enemy].avlive = true;
        _enemy[enemy].direction = UP;
        _enemy[enemy].weak = false;
    }
}

void Pacman::enemyMove(void)
{
    // blue
    if (_enemy[0].avlive == true) {
        enemyMoveRandow(0);
    } else {
        enemyReturnToHome(0);
    }
    // pink
    if (_enemy[1].avlive == true) {
        if (_enemy[1].weak == true) {
            enemyMoveRandow(1);
        } else {
            t_myopen ghost;
            t_myopen target = nextPositionPacman();
            ghost.x = _enemy[1].x;
            ghost.y = _enemy[1].y;
            t_myopen next = nextPositionGhost(ghost, target, getGrid());
            // TODO check direction, and hadle error
            if (next.x != -1 && next.y != -1) {
            if (next.x > _enemy[1].x)
                    _enemy[1].direction = RIGHT;
                else if (next.x < _enemy[1].x)
                    _enemy[1].direction = LEFT;
                else if (next.y > _enemy[1].y)
                    _enemy[1].direction = DOWN;
                else if (next.y < _enemy[1].y)
                    _enemy[1].direction = UP;
                _enemy[1].x = next.x;
                _enemy[1].y = next.y;
            }
        }
    } else {
        enemyReturnToHome(1);
    }
    // orange
    if (_enemy[2].avlive == true) { // TODO around pacman
        enemyMoveRandow(2);
    } else {
        enemyReturnToHome(2);
    }
    // red
    if (_enemy[3].avlive == true) {
        if (_enemy[3].weak == true) {
            enemyMoveRandow(3);
        } else {
            t_myopen ghost;
            t_myopen target;
            target.x = _pos_x;
            target.y = _pos_y;
            ghost.x = _enemy[3].x;
            ghost.y = _enemy[3].y;
            t_myopen next = nextPositionGhost(ghost, target, getGrid());
            // TODO check direction, and hadle error
            if (next.x != -1 && next.y != -1) {
                if (next.x > _enemy[3].x)
                    _enemy[3].direction = RIGHT;
                else if (next.x < _enemy[3].x)
                    _enemy[3].direction = LEFT;
                else if (next.y > _enemy[3].y)
                    _enemy[3].direction = DOWN;
                else if (next.y < _enemy[3].y)
                    _enemy[3].direction = UP;
                _enemy[3].x = next.x;
                _enemy[3].y = next.y;
            }
        }
    } else {
        enemyReturnToHome(3);
    }
    // TODO enemy back from dead
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
