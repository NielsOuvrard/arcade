/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-arcade-adam.elaoumari [WSL : Ubuntu]
** File description:
** Core
*/

#include "Core.hpp"

Core::Core(const std::string displayLibPath)
{
    try {
        displayLib = new DLLoader<IDisplayModule>(displayLibPath);
        currentRuntimeGraphicDisplay = displayLibPath;
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

void Core::displayMenu()
{
    IDisplayModule *module = displayLib->getInstance();
    Menu myMenu = Menu(gameLibs, gfxLibs, currentRuntimeGraphicDisplay);
    module->init();
    while (myMenu.getGameStatus() != IGameModule::FINISHED) {
        module->update(myMenu.getInfos());
        module->draw();
        myMenu.update(module->getEvent());
        if (myMenu.getCurrentRuntimeGraphicDisplay() != currentRuntimeGraphicDisplay) {
            currentRuntimeGraphicDisplay = myMenu.getCurrentRuntimeGraphicDisplay();
            module->stop();
            delete module;
            displayLib = new DLLoader<IDisplayModule>(currentRuntimeGraphicDisplay);
            module = displayLib->getInstance();
            module->init();
        }
    }
    selectedGameLib = myMenu.getSelectedGameLib();
    selectedDisplayLib = myMenu.getSelectedDisplayLib();
    module->stop();
    delete module;
    if (myMenu.getSelectedStatus())
        mainLoop();
}

void Core::mainLoop()
{
    DLLoader<IDisplayModule> *displayLib = new DLLoader<IDisplayModule> (selectedDisplayLib);
    DLLoader<IGameModule> *gameLib = new DLLoader<IGameModule> (selectedGameLib);
    IGameModule *game = gameLib->getInstance();
    IDisplayModule *display = displayLib->getInstance();
    display->init();
    display->saveTextures(game->getTextures());
    game->startGame();
    currentRuntimeGraphicDisplay = selectedDisplayLib;
    game->setCurrentRuntimeGraphicDisplay(selectedDisplayLib);
    while (game->getGameStatus() != IGameModule::FINISHED) {
        display->update(game->getInfos());
        display->draw();
        game->update(display->getEvent());
        if (game->getCurrentRuntimeGraphicDisplay() != currentRuntimeGraphicDisplay) {
            currentRuntimeGraphicDisplay = game->getCurrentRuntimeGraphicDisplay();
            display->stop();
            delete display;
            displayLib = new DLLoader<IDisplayModule>(currentRuntimeGraphicDisplay);
            display = displayLib->getInstance();
            display->init();
        }
    }
    display->stop();
    delete displayLib;
    delete gameLib;
}