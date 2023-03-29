/*
** EPITECH PROJECT, 2022
** src_solver
** File description:
** free
*/

#include "pathfinding.hpp"

void free_list(t_par *par)
{
    free_arr(par);
    free_linked(par);
    free_nodes(par);
    delete par;
}

void free_arr(t_par *par)
{
    for (int j = 0; par->arr[j] ; j++) {
        delete[] par->arr[j];
    }
    delete[] par->arr;
}

void free_linked(t_par *par)
{
    t_open **tmp = &par->open;
    t_open *tmp2 = *tmp;
    while (tmp2 != NULL) {
        t_open *next = tmp2->next;
        delete tmp2;
        tmp2 = next;
    }
}
