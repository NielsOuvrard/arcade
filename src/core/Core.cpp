/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-arcade-adam.elaoumari [WSL : Ubuntu]
** File description:
** Core
*/

#include "Core.hpp"

Core::Core(const std::string displayLibPath)
{
    int i = 0;
    try {
        std::string path = "lib/";
        for (const auto &entry : std::filesystem::directory_iterator(path)) {
            if (entry.path().extension() == ".so") {
                DLLoader<void> *val = new DLLoader<void> (entry.path());
                std::string type = val->getInstanceType();
                if (type == "Graphic") {
                    gfxLibs.insert(gfxLibs.end(),entry.path());
                    std::cout << "GRAPHIC LIB : " << entry.path() << std::endl;
                    if (entry.path() == displayLibPath) {
                        DLLoader<IDisplayModule> *val = new DLLoader<IDisplayModule> (entry.path());
                        selectedDisplay = val->getInstance();
                        std::cout << "SELECTED GRAPHIC LIB : " << entry.path() << std::endl;
                        loadedLibsDisplay.insert(loadedLibsDisplay.end(), val);
                        currentDisplayIndex = i;
                    }
                    i++;
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
    if (selectedDisplay == nullptr) {
        std::cerr << "Provided display lib is not accessible." << std::endl;
        exit(84);
    }
}

Core::~Core()
{
    for (auto val : gameList) {
        std::cout << "la" << std::endl;
        delete val;
    }
    for (auto val : menuList) {
        std::cout << "bas" << std::endl;
        delete val;
    }
    for (auto val : loadedLibs) {
        delete val;
    }
    for (auto val : loadedLibsDisplay) {
        delete val;
    }
}

void Core::displayMenu()
{
    Menu myMenu = Menu(gameLibs, gfxLibs);
    selectedDisplay->init();
    while (myMenu.getGameStatus() != IGameModule::FINISHED && myMenu.getGameStatus() != IGameModule::CLOSED) {
        selectedDisplay->update(myMenu.getInfos());
        selectedDisplay->draw();
        std::string key = selectedDisplay->getEvent();
        if (key == "F1") {
            if (currentDisplayIndex == gfxLibs.size() - 1)
                currentDisplayIndex = 0;
            else
                currentDisplayIndex++;
            selectedDisplay->stop();
            delete selectedDisplay;
            DLLoader<IDisplayModule> *val = new DLLoader<IDisplayModule> (gfxLibs[currentDisplayIndex]);
            selectedDisplay = val->getInstance();
            delete val;
            selectedDisplay->init();
        } else {
            myMenu.update(key);
        }
    }
    if (currentDisplayIndex != myMenu.getSelectedDisplayLibIndex()) {
        delete selectedDisplay;
        DLLoader<IDisplayModule> *val = new DLLoader<IDisplayModule> (gfxLibs[currentDisplayIndex]);
        selectedDisplay = val->getInstance();
        delete val;
    }
    currentGameIndex = myMenu.getSelectedGameLibIndex();
    currentDisplayIndex = myMenu.getSelectedDisplayLibIndex();
    selectedDisplay->stop();
    if (myMenu.getSelectedStatus()) {
        gameMenuLoop();
    }
}

void Core::gameMenuLoop()
{
    selectedGame = gameList[currentGameIndex];
    selectedMenu = menuList[0];
    selectedDisplay->init();
    selectedMenu->resetGame();
    selectedMenu->startGame();
    selectedMenu->setText("Game", selectedGame->getName());
    while (selectedMenu->getGameStatus() != IGameModule::FINISHED
    && selectedMenu->getGameStatus() != IGameModule::MENU
    && selectedMenu->getGameStatus() != IGameModule::CLOSED) {
        selectedDisplay->update(selectedMenu->getInfos());
        selectedDisplay->draw();
        std::string key = selectedDisplay->getEvent();
        if (key == "F1") {
            if (currentDisplayIndex == gfxLibs.size() - 1)
                currentDisplayIndex = 0;
            else
                currentDisplayIndex++;
            selectedDisplay->stop();
            delete selectedDisplay;
            DLLoader<IDisplayModule> *val = new DLLoader<IDisplayModule> (gfxLibs[currentDisplayIndex]);
            selectedDisplay = val->getInstance();
            delete val;
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
    } else if (selectedMenu->getGameStatus() == IGameModule::FINISHED ){
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
    while (selectedGame->getGameStatus() != IGameModule::FINISHED && selectedGame->getGameStatus() != IGameModule::CLOSED) {
        selectedDisplay->update(selectedGame->getInfos());
        selectedDisplay->draw();
        std::string key = selectedDisplay->getEvent();
        if (key == "F1") {
            if (currentDisplayIndex == gfxLibs.size() - 1)
                currentDisplayIndex = 0;
            else
                currentDisplayIndex++;
            selectedDisplay->stop();
            delete selectedDisplay;
            DLLoader<IDisplayModule> *val = new DLLoader<IDisplayModule> (gfxLibs[currentDisplayIndex]);
            selectedDisplay = val->getInstance();
            delete val;
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
    if (selectedGame->getGameStatus() != IGameModule::CLOSED)
        endGameLoop();
}

void Core::endGameLoop()
{
    selectedGame = gameList[currentGameIndex];
    selectedMenu = menuList[1];
    selectedDisplay->init();
    selectedMenu->startGame();
    while (selectedMenu->getGameStatus() != IGameModule::FINISHED &&
    selectedMenu->getGameStatus() != IGameModule::MENU &&
    selectedMenu->getGameStatus() != IGameModule::RESTART) {
        selectedDisplay->update(selectedMenu->getInfos());
        selectedDisplay->draw();
        std::string key = selectedDisplay->getEvent();
        if (key == "F1") {
            if (currentDisplayIndex == gfxLibs.size() - 1)
                currentDisplayIndex = 0;
            else
                currentDisplayIndex++;
            selectedDisplay->stop();
            delete selectedDisplay;
            DLLoader<IDisplayModule> *val = new DLLoader<IDisplayModule> (gfxLibs[currentDisplayIndex]);
            selectedDisplay = val->getInstance();
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
