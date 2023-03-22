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
                } else if (type == "Menu") {
                    std::cout << "MENU LIB : " << entry.path() << std::endl;;
                    menuLibs.insert(menuLibs.end(),entry.path());
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

void Core::findIndex()
{
    for (int i = 0; i < gameLibs.size(); i++) {
        if (gameLibs[i] == selectedGameLib) {
            currentGameIndex = i;
            break;
        }
    }
    for (int i = 0; i < gfxLibs.size(); i++) {
        if (gfxLibs[i] == selectedDisplayLib) {
            currentDisplayIndex = i;
            break;
        }
    }
}

void Core::displayMenu()
{
    IDisplayModule *module = displayLib->getInstance();
    Menu myMenu = Menu(gameLibs, gfxLibs);
    findIndex();
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
        gameMenuLoop();
}

void Core::initializeGames()
{
    for (int i = 0; i < gameLibs.size(); i++) {
        DLLoader<IGameModule> *gameLib = new DLLoader<IGameModule> (gameLibs[i]);
        games.insert(games.end(), gameLib->getInstance());
    }
}

void Core::gameMenuLoop()
{
    displayLib = new DLLoader<IDisplayModule> (selectedDisplayLib);
    gameLib = new DLLoader<IGameModule> (menuLibs[0]);
    menu = gameLib->getInstance();
    display = displayLib->getInstance();
    initializeGames();
    findIndex();
    display->init();
    menu->startGame();
    menu->setText("Game", games[currentGameIndex]->getName());
    while (menu->getGameStatus() != IGameModule::FINISHED && menu->getGameStatus() != IGameModule::MENU) {
        display->update(menu->getInfos());
        display->draw();
        std::string key = display->getEvent();
        if (key == "F1") {
            if (currentDisplayIndex == gfxLibs.size() - 1)
                currentDisplayIndex = 0;
            else
                currentDisplayIndex++;
            display->stop();
            delete display;
            selectedDisplayLib = gfxLibs[currentDisplayIndex];
            displayLib = new DLLoader<IDisplayModule>(gfxLibs[currentDisplayIndex]);
            display = displayLib->getInstance();
            display->init();
        } else if (key == "F2") {
            if (currentGameIndex == gameLibs.size() - 1)
                currentGameIndex = 0;
            else
                currentGameIndex++;
            selectedGameLib = gameLibs[currentGameIndex];
            menu->setText("Game", games[currentGameIndex]->getName());
        } else {
            menu->update(key);
        }
    }
    display->stop();
    if (menu->getGameStatus() == IGameModule::MENU) {
        delete gameLib;
        displayMenu();
    } else {
        delete gameLib;
        delete displayLib;
        mainLoop();
    }
}

void Core::mainLoop()
{
    displayLib = new DLLoader<IDisplayModule> (selectedDisplayLib);
    gameLib = new DLLoader<IGameModule> (selectedGameLib);
    display = displayLib->getInstance();
    display->init();
    findIndex();
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
