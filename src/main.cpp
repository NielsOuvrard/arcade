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
#include "Core.hpp"
int main(void)
{
    Core newCore = Core();
    std::vector<std::string> list = newCore.getGfxLibs();
    for (auto val : list) {
        DLLoader<IDisplayModule> *loader = new DLLoader<IDisplayModule> (val);
        IDisplayModule *module = loader->getInstance();
        module->init();
        while (1) {
            module->draw();
            if (module->getEvent() == "e")
                break;
        }
        module->stop();
        delete loader;
    }
    return 0;
}
