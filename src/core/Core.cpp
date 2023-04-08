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
        for (const auto &entry : std::filesystem::directory_iterator(path)) {
            if (entry.path().extension() == ".so") {
                DLLoader<void> loader = DLLoader<void>(entry.path());
                std::string type = loader.getInstanceType();
                if (type == "Graphic") {
                    gfxLibs.insert(gfxLibs.end(),entry.path());
                    std::cout << "GRAPHIC LIB : " << entry.path() << std::endl;
                    if (entry.path() == menuDisplayLibPath) {
                        currentDisplayIndex = i;
                    }
                    i++;
                } else if (type == "Menu") {
                    DLLoader<IGameModule> *menu = new DLLoader<IGameModule> (entry.path());
                    loadedLibs.insert(loadedLibs.end(),menu);
                    IGameModule *menuLib = menu->getInstance();
                    menuList.insert(menuList.end(), menuLib);
                    menuLibs.insert(menuLibs.end(),entry.path());
                    std::cout << "MENU LIB : " << entry.path() << std::endl;;
                } else {
                    DLLoader<IGameModule> *gameLib = new DLLoader<IGameModule> (entry.path());
                    loadedLibs.insert(loadedLibs.end(),gameLib);
                    std::cout << gameLib->getInstanceType() << std::endl;
                    IGameModule *game = gameLib->getInstance();
                    gameList.insert(gameList.end(), game);
                    gameLibs.insert(gameLibs.end(),entry.path());
                    std::cout << "GAME LIB : " << entry.path() << std::endl;
                }
            }
        }
        DLLoader<IDisplayModule> *val = new DLLoader<IDisplayModule> (gfxLibs[currentDisplayIndex]);
        loadedDisplayLib = val;
        selectedDisplay = val->getInstance();
        selectedDisplay->init();
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
    for (auto val : gameList) {
        delete val;
    }
    for (auto val : menuList) {
        delete val;
    }
    for (auto val : loadedLibs) {
        delete val;
    }
    if (selectedDisplay) {
        delete selectedDisplay;
        std::cout << "delete display" << std::endl;
    }
    if (loadedDisplayLib) {
        delete loadedDisplayLib;
        std::cout << "delete display lib" << std::endl;
    }
}

void Core::loadGraphicLib(std::string path)
{
    std::cout << "je rentre ici" << std::endl;
    if (selectedDisplay != nullptr) {
        selectedDisplay->stop();
        delete selectedDisplay;
    }
    if (loadedDisplayLib != nullptr) {
        delete loadedDisplayLib;
    }
    DLLoader<IDisplayModule> *val = new DLLoader<IDisplayModule> (path);
    loadedDisplayLib = val;
    selectedDisplay = val->getInstance();
    selectedDisplay->init();
}

void Core::displayMenu()
{
    Menu myMenu = Menu(gameLibs, gfxLibs, menuDisplayLibPath);
    while (myMenu.getGameStatus() != IGameModule::FINISHED && myMenu.getGameStatus() != IGameModule::CLOSED) {
        selectedDisplay->update(myMenu.getInfos());
        selectedDisplay->draw();
        std::string key = selectedDisplay->getEvent();
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
    if (currentDisplayIndex != myMenu.getSelectedDisplayLibIndex() && myMenu.getGameStatus() == IGameModule::FINISHED) {
        loadGraphicLib(gfxLibs[myMenu.getSelectedDisplayLibIndex()]);
    }
    currentGameIndex = myMenu.getSelectedGameLibIndex();
    currentDisplayIndex = myMenu.getSelectedDisplayLibIndex();
    selectedDisplay->resetDisplay();
    name = myMenu.getName().substr(18, name.length() - 18);
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);
    if (myMenu.getSelectedStatus()) {
        gameMenuLoop();
    }
}

void Core::writeScore()
{
    std::ifstream file("scores/" + selectedGame->getName() + ".txt");
    std::string file_name = selectedGame->getName();
    std::transform(file_name.begin(), file_name.end(), file_name.begin(), ::tolower);
    if (!file) {
        file.close();
        std::ofstream file2("scores/" + file_name + ".txt");
        file2 << selectedGame->getScore() << " " << name << std::endl;
    } else {
        std::string line;
        std::string score;
        getline(file, line);
        std::ofstream file2("scores/" + file_name + ".txt");
        score = line.substr(0, line.find(" "));
        if (std::stoi(score) < selectedGame->getScore()) {
            file2 << selectedGame->getScore() << " " << name << std::endl;
        } else {
            file2 << line << std::endl;
        }
        file2.close();
    }
}

void Core::gameMenuLoop()
{
    selectedGame = gameList[currentGameIndex];
    selectedMenu = menuList[0];
    selectedDisplay->resetDisplay();
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
            loadGraphicLib(gfxLibs[currentDisplayIndex]);
        } else if (key == "F2") {
            selectedDisplay->resetDisplay();
            if (currentGameIndex == gameLibs.size() - 1)
                currentGameIndex = 0;
            else
                currentGameIndex++;
            selectedGame = gameList[currentGameIndex];
            selectedDisplay->saveTextures(selectedGame->getTextures());
            selectedMenu->setText("Game", selectedGame->getName());
        } else {
            selectedMenu->update(key);
        }
    }

    if (selectedMenu->getGameStatus() == IGameModule::MENU) {
        selectedGame->resetGame();
        selectedDisplay->resetDisplay();
        displayMenu();
    } else if (selectedMenu->getGameStatus() == IGameModule::FINISHED ){
        selectedGame->resetGame();
        mainLoop();
    }
}

void Core::mainLoop()
{
    selectedGame = gameList[currentGameIndex];
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
            loadGraphicLib(gfxLibs[currentDisplayIndex]);
            selectedDisplay->saveTextures(selectedGame->getTextures());
        } else if (key == "F2") {
            selectedDisplay->resetDisplay();
            if (currentGameIndex == gameLibs.size() - 1)
                currentGameIndex = 0;
            else
                currentGameIndex++;
            selectedGame = gameList[currentGameIndex];
            selectedDisplay->saveTextures(selectedGame->getTextures());
        } else {
            selectedGame->update(key);
        }
    }
    writeScore();
    if (selectedGame->getGameStatus() != IGameModule::CLOSED) {
        selectedDisplay->resetDisplay();
        endGameLoop();
    }
    selectedDisplay->stop();
}

void Core::endGameLoop()
{
    int score = selectedGame->getScore();
    selectedGame = gameList[currentGameIndex];
    selectedMenu = menuList[1];
    selectedMenu->startGame();
    selectedMenu->setText("Score", "Score:" + std::to_string(score));
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
            loadGraphicLib(gfxLibs[currentDisplayIndex]);
        } else {
            selectedMenu->update(key);
        }
    }
    if (selectedMenu->getGameStatus() == IGameModule::MENU) {
        gameMenuLoop();
    } else if (selectedMenu->getGameStatus() == IGameModule::RESTART) {
        selectedGame->resetGame();
        mainLoop();
    }
    selectedDisplay->stop();
}
