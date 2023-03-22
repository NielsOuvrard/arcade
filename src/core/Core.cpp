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
        selectedDisplayLib = displayLibPath;
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

void findIndex(std::string &selectedLib, std::vector<std::string> &libs, int &currentIndex)
{
    for (int i = 0; i < libs.size(); i++) {
        if (libs[i] == selectedLib) {
            currentIndex = i;
            break;
        }
    }
}

void Core::displayMenu()
{
    IDisplayModule *module = displayLib->getInstance();
    Menu myMenu = Menu(gameLibs, gfxLibs);
    findIndex(selectedDisplayLib, gfxLibs, currentDisplayIndex);
    module->init();
    while (myMenu.getGameStatus() != IGameModule::FINISHED) {
        module->update(myMenu.getInfos());
        module->draw();
        std::string key = module->getEvent();
        if (key == "F1") {
            if (currentDisplayIndex == gfxLibs.size() - 1)
                currentDisplayIndex = 0;
            else
                currentDisplayIndex++;
            module->stop();
            delete module;
            displayLib = new DLLoader<IDisplayModule>(gfxLibs[currentDisplayIndex]);
            module = displayLib->getInstance();
            module->init();
        } else {
            myMenu.update(key);
        }
    }
    selectedGameLib = myMenu.getSelectedGameLib();
    selectedDisplayLib = myMenu.getSelectedDisplayLib();
    module->stop();
    delete module;
    if (myMenu.getSelectedStatus())
        mainLoop();
}

void initializeGames(std::vector<IGameModule *> &games, std::vector<std::string> &gameLibs)
{
    for (int i = 0; i < gameLibs.size(); i++) {
        DLLoader<IGameModule> *game = new DLLoader<IGameModule> (gameLibs[i]);
        games.insert(games.end(), game->getInstance());
    }
}

void Core::mainLoop()
{
    DLLoader<IDisplayModule> *displayLib = new DLLoader<IDisplayModule> (selectedDisplayLib);
    DLLoader<IGameModule> *gameLib = new DLLoader<IGameModule> (selectedGameLib);
    IDisplayModule *display = displayLib->getInstance();
    initializeGames(games, gameLibs);
    findIndex(selectedDisplayLib, gfxLibs, currentDisplayIndex);
    findIndex(selectedGameLib, gameLibs, currentGameIndex);
    display->init();
    display->saveTextures(games[currentGameIndex]->getTextures());
    games[currentGameIndex]->startGame();
    while (games[currentGameIndex]->getGameStatus() != IGameModule::FINISHED) {
        display->update(games[currentGameIndex]->getInfos());
        display->draw();
        std::string key = display->getEvent();
        if (key == "F1") {
            if (currentDisplayIndex == gfxLibs.size() - 1)
                currentDisplayIndex = 0;
            else
                currentDisplayIndex++;
            display->stop();
            delete display;
            displayLib = new DLLoader<IDisplayModule>(gfxLibs[currentDisplayIndex]);
            display = displayLib->getInstance();
            display->init();
            display->saveTextures(games[currentGameIndex]->getTextures());
        } else if (key == "F2") {
            if (currentGameIndex == gameLibs.size() - 1)
                currentGameIndex = 0;
            else
                currentGameIndex++;
        } else {
            games[currentGameIndex]->update(key);
        }
    }
    display->stop();
    delete displayLib;
    delete gameLib;
}