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
        std::string path = "lib/";
        for (const auto &entry : std::filesystem::directory_iterator(path)) {
            if (entry.path().extension() == ".so") {
                DLLoader<void> *val = new DLLoader<void> (entry.path());

                std::string type = val->getInstanceType();
                if (type == "Graphic") {
                    IDisplayModule *display = reinterpret_cast<IDisplayModule *> (val->getInstance());
                    displayList.insert(displayList.end(), display);
                    if (entry.path() == displayLibPath) {
                        selectedDisplay = display;
                    }
                    gfxLibs.insert(gfxLibs.end(),entry.path());
                } else if (type == "Menu") {
                    std::cout << "MENU LIB : " << entry.path() << std::endl;;
                    IGameModule *menuLib = reinterpret_cast<IGameModule *> (val->getInstance());
                    menu = menuLib;
                    menuLibs.insert(menuLibs.end(),entry.path());
                } else {
                    IGameModule *game = reinterpret_cast<IGameModule *> (val->getInstance());
                    gameList.insert(gameList.end(), game);
                    gameLibs.insert(gameLibs.end(),entry.path());
                    std::cout << "GAME LIB : " << entry.path() << std::endl;;
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
    for (auto val : displayList) {
        delete val;
    }
    for (auto val : gameList) {
        delete val;
    }
    if (menu)
        delete menu;
}

void Core::displayMenu()
{
    Menu myMenu = Menu(gameLibs, gfxLibs);
    selectedDisplay->init();
    while (myMenu.getGameStatus() != IGameModule::FINISHED) {
        selectedDisplay->update(myMenu.getInfos());
        selectedDisplay->draw();
        std::string key = selectedDisplay->getEvent();
        if (key == "F1") {
            if (currentDisplayIndex == gfxLibs.size() - 1)
                currentDisplayIndex = 0;
            else
                currentDisplayIndex++;
            selectedDisplay->stop();
            selectedDisplay = displayList[currentDisplayIndex];
            selectedDisplay->init();
        } else {
            myMenu.update(key);
        }
    }
    currentGameIndex = myMenu.getSelectedGameLibIndex();
    currentDisplayIndex = myMenu.getSelectedDisplayLibIndex();
    selectedDisplay->stop();
    if (myMenu.getSelectedStatus())
        gameMenuLoop();
}

void Core::gameMenuLoop()
{
    selectedDisplay = displayList[currentDisplayIndex];
    selectedGame = gameList[currentGameIndex];
    selectedDisplay->init();
    menu->startGame();
    menu->setText("Game", selectedGame->getName());
    while (menu->getGameStatus() != IGameModule::FINISHED && menu->getGameStatus() != IGameModule::MENU) {
        selectedDisplay->update(menu->getInfos());
        selectedDisplay->draw();
        std::string key = selectedDisplay->getEvent();
        if (key == "F1") {
            if (currentDisplayIndex == gfxLibs.size() - 1)
                currentDisplayIndex = 0;
            else
                currentDisplayIndex++;
            selectedDisplay->stop();
            selectedDisplay = displayList[currentDisplayIndex];
            selectedDisplay->init();
        } else if (key == "F2") {
            if (currentGameIndex == gameLibs.size() - 1)
                currentGameIndex = 0;
            else
                currentGameIndex++;
            selectedGame = gameList[currentGameIndex];
            menu->setText("Game", selectedGame->getName());
        } else {
            menu->update(key);
        }
    }
    selectedDisplay->stop();
    if (menu->getGameStatus() == IGameModule::MENU) {
        displayMenu();
    } else {
        mainLoop();
    }
}

void Core::mainLoop()
{
    selectedGame = gameList[currentGameIndex];
    selectedDisplay->init();
    selectedDisplay->saveTextures(selectedGame->getTextures());
    selectedGame->startGame();
    while (selectedGame->getGameStatus() != IGameModule::FINISHED) {
        selectedDisplay->update(selectedGame->getInfos());
        selectedDisplay->draw();
        std::string key = selectedDisplay->getEvent();
        if (key == "F1") {
            if (currentDisplayIndex == gfxLibs.size() - 1)
                currentDisplayIndex = 0;
            else
                currentDisplayIndex++;
            selectedDisplay->stop();
            selectedDisplay = displayList[currentDisplayIndex];
            selectedDisplay->init();
            selectedDisplay->saveTextures(selectedGame->getTextures());
        } else if (key == "F2") {
            if (currentGameIndex == gameLibs.size() - 1)
                currentGameIndex = 0;
            else
                currentGameIndex++;
            selectedGame = gameList[currentGameIndex];
        } else {
            selectedGame->update(key);
        }
    }
    selectedDisplay->stop();
}
