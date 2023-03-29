/*
**  ______   ______     ______     __    __     ______     __   __
** /\  == \ /\  __ \   /\  ___\   /\ "-./  \   /\  __ \   /\ "-.\ \
** \ \  _-/ \ \  __ \  \ \ \____  \ \ \-./\ \  \ \  __ \  \ \ \-.  \
**  \ \_\    \ \_\ \_\  \ \_____\  \ \_\ \ \_\  \ \_\ \_\  \ \_\\"\_\
**   \/_/     \/_/\/_/   \/_____/   \/_/  \/_/   \/_/\/_/   \/_/ \/_/
**
*/

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <chrono>
#include <memory>
#include "pathfinding.hpp"

t_myopen newNode(int x, int y)
{
    t_myopen pos;
    pos.x = x;
    pos.y = y;
    return pos;
}

t_myopen findThis(std::vector<std::vector<int>> _grid, int target)
{
    t_myopen begin;
    int y = 0;
    for (auto &line : _grid) {
        int x = 0;
        for (auto &c : line) {
            if (c == target)
                return newNode(x, y);
            x++;
        }
        y++;
    }
    return newNode(-1, -1);
}

char **grid_to_array(std::vector<std::vector<int>> _grid)
{
    char **array = new char*[_grid.size() + 1];
    int i = 0;
    for (auto &line : _grid) {
        array[i] = new char[line.size() + 1];
        int j = 0;
        for (auto &c : line) {
            if (c == -2)
                array[i][j] = '#';
            else
                array[i][j] = '*';
            j++;
        }
        array[i][j] = '\0';
        i++;
    }
    array[i] = NULL;
    return array;
}

t_par *initialise_struct_par (std::vector<std::vector<int>> _grid, int end_x, int end_y)
{
    t_par *par = new t_par;
    par->open = NULL;
    par->arr = grid_to_array(_grid);
    par->arr_len = my_arrlen(par->arr);
    par->str_len = my_strlen(par->arr[0]);
    par->end_x = end_x;
    par->end_y = end_y;
    malloc_list(par);
    initialize_nodes(par);
    par->current_x = 0;
    par->current_y = 0;
    par->nodes[0][0].g_cost = 0;
    par->nodes[0][0].x = 0;
    par->nodes[0][0].y = 0;
    par->nodes[0][0].parent = NULL;
    par->list_len = 0;
    return par;
}

t_myopen astar(t_par *par)
{
    int i = 0;
    while (par->list_len != 0) {
        if (par->current_x == par->end_x
        && par->current_y == par->end_y) {
            i = 0;
            return send_next_pos(par);
        }
        pick_square(par);
        check_allsquares(par, par->current_x, par->current_y);
        i++;
    }
    free_list(par);
    return newNode(-1, -1);
}

t_myopen nextPositionGhost(t_myopen ghost, t_myopen target, std::vector<std::vector<int>> _grid)
{
    t_par *par = initialise_struct_par(_grid, target.x, target.y);
    check_allsquares(par, ghost.x, ghost.y);
    return astar(par);
}
