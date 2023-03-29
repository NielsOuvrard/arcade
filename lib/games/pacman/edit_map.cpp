/*
** EPITECH PROJECT, 2022
** src_solver
** File description:
** edit_map
*/

#include "pathfinding.hpp"

t_myopen send_next_pos(t_par *par)
{
    int tmp_y = par->current_y;
    int tmp_x = par->current_x;
    par->arr[tmp_y][tmp_x] = 'o';
    t_myopen tmp = newNode(-1, -1);
    while (par->nodes[tmp_y][tmp_x].parent) {
        int x = par->nodes[tmp_y][tmp_x].parent->x;
        int y = par->nodes[tmp_y][tmp_x].parent->y;
        if (!par->nodes[tmp_y][tmp_x].parent->parent)
            tmp = newNode(tmp_x, tmp_y);
        tmp_x = x;
        tmp_y = y;
    }
    free_list(par);
    return tmp;
}

void write_tomap(t_par *par)
{
    int tmp_y = par->current_y;
    int tmp_x = par->current_x;
    par->arr[tmp_y][tmp_x] = 'o';
    while (par->nodes[tmp_y][tmp_x].parent) {
        int x = par->nodes[tmp_y][tmp_x].parent->x;
        int y = par->nodes[tmp_y][tmp_x].parent->y;
        par->arr[y][x] = 'o';
        tmp_x = x;
        tmp_y = y;
    }
}
