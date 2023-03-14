/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-arcade-adam.elaoumari
** File description:
** main
*/


#include "display/IDisplay.hpp"
#include "core/DLLoader.hpp"
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <chrono>
#include <thread>

int main(void)
{
    std::string libPath = "lib/arcade_sfml.so";
    DLLoader<IDisplayModule> *val = new DLLoader<IDisplayModule> (libPath);
    IDisplayModule *module = val->getInstance();
    module->init();
    module->draw();
    std::chrono::milliseconds timespan(1000); // or whatever
    std::this_thread::sleep_for(timespan);            
    module->stop();
    libPath = "lib/arcade_ncurses.so";
    delete val;
    return 0;
}
