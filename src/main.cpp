/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-arcade-adam.elaoumari
** File description:
** main
*/


#include "IDisplayModule.hpp"
#include "core/DLLoader.hpp"
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include "Core.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
        exit(84);
    srand(time(NULL));
    try {
        Core newCore = Core(av[1]);
        newCore.init();
        newCore.displayMenu();
    } catch (std::exception &e){
        std::cerr << e.what() << std::endl;
        exit(84);
    }
}
