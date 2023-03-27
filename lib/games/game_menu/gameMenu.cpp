/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-arcade-adam.elaoumari [WSL : Ubuntu]
** File description:
** GameMenu
*/

#include "gameMenu.hpp"

GameMenu::GameMenu()
{
    float x = 0, y = 0;
    Entity gameEntity = {
        -1,
        "Game",
        "E9967A",
        x,
        y,
        true,
        true,
        {255, 255, 255},
        {0, 0, 0}
    };
    y += 1;
    setNewEntity("Game", gameEntity);
    gameEntity = {
        -1,
        "Start",
        "E9967A",
        x,
        y,
        true,
        true,
        {255, 255, 255},
        {0, 0, 0}
    };
    y += 1;
    setNewEntity("Start", gameEntity);
    gameEntity = {
        -1,
        "Quit",
        "E9967A",
        x,
        y,
        false,
        false,
        {255, 255, 255},
        {0, 0, 0}
    };
    y += 1;
    setNewEntity("Quit", gameEntity);
}

GameMenu::~GameMenu()
{
}

void GameMenu::update(std::string key)
{
    if (key.empty())
        return;
    if (key == "close") {
        setGameStatus(CLOSED);
    }
    if (options.size() != 0) {
        if (key == "Enter") {
            if (getSelectedOption() == "Quit") {
                setGameStatus(MENU);
            } else {
                setGameStatus(FINISHED);
            }
            return;
        }
        if (key == "DownArrow" && (selectedOptionIndex + 1) < options.size()) {
            std::string currentSelectedOption = options[selectedOptionIndex];
            std::string newSelectedOption = options[selectedOptionIndex + 1];
            getEntity(currentSelectedOption).underline = false;
            getEntity(currentSelectedOption).bold = false;
            getEntity(newSelectedOption).underline = true;
            getEntity(newSelectedOption).bold = true;
            selectedOptionIndex += 1;
            return;
        }
        if (key == "UpArrow" && selectedOptionIndex != 0) {
            std::string currentSelectedOption = options[selectedOptionIndex];
            std::string newSelectedOption = options[selectedOptionIndex - 1];
            getEntity(currentSelectedOption).underline = false;
            getEntity(currentSelectedOption).bold = false;
            getEntity(newSelectedOption).underline = true;
            getEntity(newSelectedOption).bold = true;
            selectedOptionIndex -= 1;
            return;
        }
    }
}

std::vector<std::string> GameMenu::getTextures() {
    return {};
}

void GameMenu::resetGame(void)
{
    _entities.clear();
        float x = 0, y = 0;
    Entity gameEntity = {
        -1,
        "Game",
        "E9967A",
        x,
        y,
        true,
        true,
        {255, 255, 255},
        {0, 0, 0}
    };
    y += 1;
    setNewEntity("Game", gameEntity);
    gameEntity = {
        -1,
        "Start",
        "E9967A",
        x,
        y,
        true,
        true,
        {255, 255, 255},
        {0, 0, 0}
    };
    y += 1;
    setNewEntity("Start", gameEntity);
    gameEntity = {
        -1,
        "Quit",
        "E9967A",
        x,
        y,
        false,
        false,
        {255, 255, 255},
        {0, 0, 0}
    };
    y += 1;
    setNewEntity("Quit", gameEntity);
    selectedOptionIndex = 0;
    hasSelected = false;
}

extern "C" IGameModule *create(void) {
    return new GameMenu();
}

extern "C" std::string getType() {
    return "Menu";
}
