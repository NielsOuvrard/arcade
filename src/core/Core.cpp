/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-arcade-adam.elaoumari [WSL : Ubuntu]
** File description:
** Core
*/

#include "Core.hpp"

Core::Core(const std::string displayLibPath)
{
    menuDisplayLibPath = displayLibPath;
}

void Core::init(void)
{
    int i = 0;
    try {
        std::string path = "lib/";
        void **lib;
        for (const auto &entry : std::filesystem::directory_iterator(path)) {
            if (entry.path().extension() == ".so") {
                lib = (void **) dlopen(entry.path().c_str(), RTLD_NOW);
                std::string (*func)(void);
                func = (std::string  (*) ()) dlsym(lib, "getType");
                std::string type = func();
                dlclose(lib);
                if (type == "Graphic") {
                    gfxLibs.insert(gfxLibs.end(),entry.path());
                    std::cout << "GRAPHIC LIB : " << entry.path() << std::endl;
                    if (entry.path() == menuDisplayLibPath) {
                        currentDisplayIndex = i;
                    }
                    i++;
                } else if (type == "Menu") {
                    std::shared_ptr<DLLoader<IGameModule>> menu = std::make_shared<DLLoader<IGameModule>> (entry.path());
                    loadedLibs.insert(loadedLibs.end(), menu);
                    std::shared_ptr<IGameModule *> menuLib = std::make_shared <IGameModule *> (menu->getInstance());
                    menuList.insert(menuList.end(), menuLib);
                    menuLibs.insert(menuLibs.end(),entry.path());
                    std::cout << "MENU LIB : " << entry.path() << std::endl;;
                } else {
                    std::shared_ptr<DLLoader<IGameModule>> gameLib = std::make_shared<DLLoader<IGameModule>> (entry.path());
                    loadedLibs.insert(loadedLibs.end(),gameLib);
                    std::shared_ptr<IGameModule *> game = std::make_shared <IGameModule *> (gameLib->getInstance());
                    gameList.insert(gameList.end(), game);
                    gameLibs.insert(gameLibs.end(),entry.path());
                    std::cout << "GAME LIB : " << entry.path() << std::endl;
                }
            }
        }
        loadGraphicLib(gfxLibs[currentDisplayIndex]);
    } catch (std::exception &e){
        throw Error("Error while loading libs.");
    }
    if (currentDisplayIndex == -1) {
        throw Error("Provided display lib is not accessible.");
    }
}

Core::~Core()
{
    std::cout << "destructor has been called" << std::endl;
}

void Core::loadGraphicLib(std::string path)
{
    std::cout << "je rentre ici" << std::endl;
    if (selectedDisplay != nullptr) {
        (*selectedDisplay)->stop();
    }
    std::shared_ptr<DLLoader<IDisplayModule>> val = std::make_shared<DLLoader<IDisplayModule>> (path);
    loadedDisplayLib = val;
    selectedDisplay = std::make_shared<IDisplayModule *> (val->getInstance());
    (*selectedDisplay)->init();
}

void Core::displayMenu()
{
    Menu myMenu = Menu(gameLibs, gfxLibs);
    while (myMenu.getGameStatus() != IGameModule::FINISHED && myMenu.getGameStatus() != IGameModule::CLOSED) {
        (*selectedDisplay)->update(myMenu.getInfos());
        (*selectedDisplay)->draw();
        std::string key = (*selectedDisplay)->getEvent();
        if (key == "F1") {
            if (currentDisplayIndex == gfxLibs.size() - 1)
                currentDisplayIndex = 0;
            else
                currentDisplayIndex++;
            loadGraphicLib(gfxLibs[currentDisplayIndex]);
        } else {
            myMenu.update(key);
        }
    }
    if (currentDisplayIndex != myMenu.getSelectedDisplayLibIndex()) {
        loadGraphicLib(gfxLibs[myMenu.getSelectedDisplayLibIndex()]);
    }
    currentGameIndex = myMenu.getSelectedGameLibIndex();
    currentDisplayIndex = myMenu.getSelectedDisplayLibIndex();
    (*selectedDisplay)->resetDisplay();
    if (myMenu.getSelectedStatus()) {
        gameMenuLoop();
    }
    (*selectedDisplay)->stop();
}

void Core::gameMenuLoop()
{
    selectedGame = gameList[currentGameIndex];
    selectedMenu = menuList[0];
    (*selectedDisplay)->resetDisplay();
    (*selectedMenu)->resetGame();
    (*selectedMenu)->startGame();
    (*selectedMenu)->setText("Game", (*selectedGame)->getName());
    while ((*selectedMenu)->getGameStatus() != IGameModule::FINISHED
    && (*selectedMenu)->getGameStatus() != IGameModule::MENU
    && (*selectedMenu)->getGameStatus() != IGameModule::CLOSED) {
        (*selectedDisplay)->update((*selectedMenu)->getInfos());
        (*selectedDisplay)->draw();
        std::string key = (*selectedDisplay)->getEvent();
        if (key == "F1") {
            if (currentDisplayIndex == gfxLibs.size() - 1)
                currentDisplayIndex = 0;
            else
                currentDisplayIndex++;
            loadGraphicLib(gfxLibs[currentDisplayIndex]);
        } else if (key == "F2") {
            if (currentGameIndex == gameLibs.size() - 1)
                currentGameIndex = 0;
            else
                currentGameIndex++;
            selectedGame = gameList[currentGameIndex];
            (*selectedMenu)->setText("Game", (*selectedGame)->getName());
        } else {
            (*selectedMenu)->update(key);
        }
    }
    if ((*selectedMenu)->getGameStatus() == IGameModule::MENU) {
        (*selectedGame)->resetGame();
        (*selectedDisplay)->resetDisplay();
        displayMenu();
    } else if ((*selectedMenu)->getGameStatus() == IGameModule::FINISHED ){
        (*selectedGame)->resetGame();
        mainLoop();
    }
    (*selectedDisplay)->stop();
}

void Core::mainLoop()
{
    selectedGame = gameList[currentGameIndex];
    (*selectedDisplay)->resetDisplay();
    (*selectedDisplay)->saveTextures((*selectedGame)->getTextures());
    (*selectedGame)->startGame();
    while ((*selectedGame)->getGameStatus() != IGameModule::FINISHED && (*selectedGame)->getGameStatus() != IGameModule::CLOSED) {
        (*selectedDisplay)->update((*selectedGame)->getInfos());
        (*selectedDisplay)->draw();
        std::string key = (*selectedDisplay)->getEvent();
        if (key == "F1") {
            if (currentDisplayIndex == gfxLibs.size() - 1)
                currentDisplayIndex = 0;
            else
                currentDisplayIndex++;
            loadGraphicLib(gfxLibs[currentDisplayIndex]);
            (*selectedDisplay)->saveTextures((*selectedGame)->getTextures());
        } else if (key == "F2") {
            if (currentGameIndex == gameLibs.size() - 1)
                currentGameIndex = 0;
            else
                currentGameIndex++;
            selectedGame = gameList[currentGameIndex];
        } else {
            (*selectedGame)->update(key);
        }
    }
    if ((*selectedGame)->getGameStatus() != IGameModule::CLOSED) {
        (*selectedDisplay)->resetDisplay();
        endGameLoop();
    }
    (*selectedDisplay)->stop();
}

void Core::endGameLoop()
{
    selectedGame = gameList[currentGameIndex];
    selectedMenu = menuList[1];
    (*selectedMenu)->startGame();
    while ((*selectedMenu)->getGameStatus() != IGameModule::FINISHED &&
    (*selectedMenu)->getGameStatus() != IGameModule::MENU &&
    (*selectedMenu)->getGameStatus() != IGameModule::RESTART) {
        (*selectedDisplay)->update((*selectedMenu)->getInfos());
        (*selectedDisplay)->draw();
        std::string key = (*selectedDisplay)->getEvent();
        if (key == "F1") {
            if (currentDisplayIndex == gfxLibs.size() - 1)
                currentDisplayIndex = 0;
            else
                currentDisplayIndex++;
            loadGraphicLib(gfxLibs[currentDisplayIndex]);
        } else {
            (*selectedMenu)->update(key);
        }
    }
    if ((*selectedMenu)->getGameStatus() == IGameModule::MENU) {
        gameMenuLoop();
    } else if ((*selectedMenu)->getGameStatus() == IGameModule::RESTART) {
        (*selectedGame)->resetGame();
        mainLoop();
    }
    (*selectedDisplay)->stop();
}
