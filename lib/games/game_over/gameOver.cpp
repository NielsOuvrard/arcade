/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-arcade-adam.elaoumari [WSL : Ubuntu]
** File description:
** GameOver
*/

#include "gameOver.hpp"

GameOver::GameOver()
{
    float x = 0, y = 0;
    Entity gameEntity = {
        -1,
        "Game Over",
        "E9967A",
        x,
        y,
        true,
        true,
        {255, 255, 255},
        {0, 0, 0}
    };
    y += 1;
    setNewEntity("GameOver", gameEntity);
    gameEntity = {
        -1,
        "Restart",
        "E9967A",
        x,
        y,
        true,
        true,
        {255, 255, 255},
        {0, 0, 0}
    };
    y += 1;
    setNewEntity("Restart", gameEntity);
    gameEntity = {
        -1,
        "Menu",
        "E9967A",
        x,
        y,
        false,
        false,
        {255, 255, 255},
        {0, 0, 0}
    };
    y += 1;
    setNewEntity("Menu", gameEntity);
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

GameOver::~GameOver()
{
}

void GameOver::update(std::string key)
{
    if (key.empty())
        return;
    if (key == "close") {
        setGameStatus(FINISHED);
    }
    if (options.size() != 0) {
        if (key == "Enter") {
            if (getSelectedOption() == "Menu") {
                setGameStatus(MENU);
            } else if (getSelectedOption() == "Restart") {
                setGameStatus(RESTART);
            } else {
                setGameStatus(FINISHED);
            }
            hasSelected = true;
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

void GameOver::resetGame(void)
{
    _entities.clear();
    float x = 0, y = 0;
    Entity gameEntity = {
        -1,
        "Game Over",
        "E9967A",
        x,
        y,
        true,
        true,
        {255, 255, 255},
        {0, 0, 0}
    };
    y += 1;
    setNewEntity("GameOver", gameEntity);
    gameEntity = {
        -1,
        "Restart",
        "E9967A",
        x,
        y,
        true,
        true,
        {255, 255, 255},
        {0, 0, 0}
    };
    y += 1;
    setNewEntity("Restart", gameEntity);
    gameEntity = {
        -1,
        "Menu",
        "E9967A",
        x,
        y,
        false,
        false,
        {255, 255, 255},
        {0, 0, 0}
    };
    y += 1;
    setNewEntity("Menu", gameEntity);
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

std::vector<std::string> GameOver::getTextures() {
    return {};
}

extern "C" IGameModule *create(void) {
    return new GameOver();
}

extern "C" void destroy(IGameModule* obj) {
    delete obj;
}

extern "C" std::string getType() {
    return "Menu";
}
