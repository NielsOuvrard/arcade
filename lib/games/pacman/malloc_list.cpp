/*
** EPITECH PROJECT, 2022
** a_star
** File description:
** malloc_list
*/

#include "pathfinding.hpp"

void malloc_list(t_par *par)
{
    int j = 0;
    par->nodes = new t_node*[par->arr_len + 1];
    int arr_len = par->arr_len;
    while (j != arr_len) {
        par->nodes[j] = new t_node[my_strlen(par->arr[j]) + 1];
        par->nodes[j]->parent = nullptr;
        j++;
    }
    j = 0;
    int i = 0;
    par->nodes[0][0].visited = 0;
}

void free_nodes(t_par *par)
{
    int j = 0;
    int arr_len = par->arr_len;
    while (j != arr_len) {
        delete[] par->nodes[j];
        j++;
    }
    delete[] par->nodes;
}

int my_arrlen(char **arr)
{
    int i = 0;
    while (arr[i] != NULL) {
        i++;
    }
    return i;
}

int my_strlen (char const *str)
{
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return (i);
}
