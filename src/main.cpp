/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-arcade-adam.elaoumari
** File description:
** main
*/


#include "display/IDisplay.hpp"
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <chrono>
#include <thread>

int main(void)
{
    void **foo =  (void **)dlopen("lib/arcade_ncurses.so",  RTLD_LAZY);
    IDisplayModule * (*fooFunc)(void);
    fooFunc = (IDisplayModule *(*) ()) dlsym(foo, "entryPoint");
    IDisplayModule *module;
    module = fooFunc();
    module->init();
    module->draw();
    std::chrono::milliseconds timespan(111605); // or whatever

    std::this_thread::sleep_for(timespan);
        module->stop();
    return 0;
}
