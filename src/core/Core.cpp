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
                    std::cout << "GRAPHIC LIB : " << entry.path() << std::endl;;
                } else if (type == "Menu") {
                    IGameModule *menuLib = reinterpret_cast<IGameModule *> (val->getInstance());
                    menuList.insert(menuList.end(), menuLib);
                    menuLibs.insert(menuLibs.end(),entry.path());
                    std::cout << "MENU LIB : " << entry.path() << std::endl;;
                } else {
                    IGameModule *game = reinterpret_cast<IGameModule *> (val->getInstance());
                    gameList.insert(gameList.end(), game);
                    gameLibs.insert(gameLibs.end(),entry.path());
                    std::cout << "GAME LIB : " << entry.path() << std::endl;;
                }
                loadedLibs.insert(loadedLibs.end(), val);
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
        std::cout << "ici" << std::endl;
        delete val;
    }
    for (auto val : gameList) {
        std::cout << "la" << std::endl;
        delete val;
    }
    // if (au)
    //     delete menu;
    for (auto val : menuList) {
        std::cout << "bas" << std::endl;
        delete val;
    }
    for (auto val : loadedLibs) {
        delete val;
    }
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
    selectedMenu = menuList[0];
    selectedDisplay->init();
    selectedMenu->resetGame();
    selectedMenu->startGame();
    selectedMenu->setText("Game", selectedGame->getName());
    while (selectedMenu->getGameStatus() != IGameModule::FINISHED && selectedMenu->getGameStatus() != IGameModule::MENU) {
        selectedDisplay->update(selectedMenu->getInfos());
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
            selectedMenu->setText("Game", selectedGame->getName());
        } else {
            selectedMenu->update(key);
        }
    }
    selectedDisplay->stop();
    if (selectedMenu->getGameStatus() == IGameModule::MENU) {
        displayMenu();
    } else {
        selectedGame->resetGame();
        mainLoop();
    }
}

void Core::mainLoop()
{
    selectedGame = gameList[currentGameIndex];
    selectedDisplay->init();
    selectedDisplay->resetDisplay();
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
    endGameLoop();
}

void Core::endGameLoop()
{
    selectedDisplay = displayList[currentDisplayIndex];
    selectedGame = gameList[currentGameIndex];
    selectedMenu = menuList[1];
    selectedDisplay->init();
    selectedMenu->startGame();
    while (selectedMenu->getGameStatus() != IGameModule::FINISHED && selectedMenu->getGameStatus() != IGameModule::MENU) {
        selectedDisplay->update(selectedMenu->getInfos());
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
            selectedMenu->update(key);
        }
    }
    selectedDisplay->stop();
    if (selectedMenu->getGameStatus() == IGameModule::MENU) {
        gameMenuLoop();
    } else if (selectedMenu->getGameStatus() == IGameModule::RESTART) {
        selectedGame->resetGame();
        mainLoop();
    }
}
