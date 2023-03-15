/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-arcade-adam.elaoumari [WSL : Ubuntu]
** File description:
** Core
*/

#include "Core.hpp"

Core::Core()
{
    try {

    std::string path = "lib/";
    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        if (entry.path().extension() == ".so") {
            DLLoader<void> *val = new DLLoader<void> (entry.path());
            std::string type = val->getInstanceType();
            if (type == "Graphic") {
                std::cout << "GFX LIB : " << entry.path() << std::endl;;
                gfxLibs.insert(gfxLibs.end(),entry.path());
            } else {
                std::cout << "GAME LIB : " << entry.path() << std::endl;;
                gameLibs.insert(gameLibs.end(),entry.path());
            }
        }
    }
    } catch (std::exception &e){
        std::cout << e.what() << std::endl;
        exit(84);
    }
}

Core::~Core()
{
    
}

