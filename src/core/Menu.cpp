/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-arcade-adam.elaoumari [WSL : Ubuntu]
** File description:
** Menu
*/

#include "Menu.hpp"

Menu::Menu(std::vector<std::string> gameLibsVal, std::vector<std::string> gfxLibsVal, std::string currentGraphicLibVal)
{
    setCurrentRuntimeGraphicDisplay(currentGraphicLibVal);
    gameLibs = gameLibsVal;
    gfxLibs = gfxLibsVal;
    float x = 0, y = 0;
    Entity gameEntity = {
        -1,
        "Game Libs",
        "E9967A",
        x,
        y,
        true,
        true,
        255,
        255,
        255
    };
    y += 1;
    setNewEntity("Game Libs", gameEntity);
    for (std::string val : gameLibs) {
        bool bold = false, underline = false;
        if (val == gameLibs.front()) {
            bold = true;
            underline = true;
        }
        Entity gameLib = {
            -1,
            val,
            "E9967A",
            x,
            y,
            bold,
            underline,
            255,
            255,
            255
        };
        setNewEntity(val, gameLib);
        y += 1;
    }
    Entity gfxEntity = { // old color type (only one color), why it's working ?
        -1,
        "GFX Libs",
        "E9967A",
        x,
        y,
        true,
        true,
        255,
        255,
        255
    };
    y += 1;
    setNewEntity("GFX Libs", gfxEntity);
    for (std::string val : gfxLibs) {
        bool bold = false, underline = false;
        if (val == gfxLibs.front()) {
            bold = true;
            underline = true;
        }
        Entity gfxLib = {
            -1,
            val,
            "E9967A",
            x,
            y,
            bold,
            underline,
            255,
            255,
            255
        };
        setNewEntity(val, gfxLib);
        y += 1;
    }
    Entity nameTitle = {
        -1,
        name,
        "E9967A",
        x,
        y,
        true,
        true,
        255,
        255,
        255
    };
    setNewEntity("nameTitle", nameTitle);
    x += 1;
    Entity sprite = {
        -1,
        "",
        "E9967A",
        x,
        y,
        true,
        true,
        {255, 0, 0},
        {0, 0, 0},
        {"snake-graphics.png"}
    };
    setNewEntity("snakeSprite", sprite);

}

Menu::~Menu()
{
}

void Menu::update(std::string key)
{
    if (key.empty())
        return;
    if (key == "close") {
        setGameStatus(FINISHED);
    }
    if (key == "Backspace" && name.length() > 18) {
        name.resize(name.length() - 1);

        _entities["nameTitle"].text = name;

    }
    if (key.length() == 1 && name.size() != 32) {
        name = name.append(key);
        _entities["nameTitle"].text = name;
        return;
    }
    if (key == "Enter" && isGameSelected && isDisplaySelected && name.length() > 19) {
        _status = FINISHED;
        return;
    }
    if (key == "F1") {
        if (_currentRuntimeGraphicDisplay == "lib/arcade_sfml.so") {
            _currentRuntimeGraphicDisplay = "lib/arcade_sdl2.so";
        } else if (_currentRuntimeGraphicDisplay == "lib/arcade_sdl2.so") {
            _currentRuntimeGraphicDisplay = "lib/arcade_ncurses.so";
        } else {
            _currentRuntimeGraphicDisplay = "lib/arcade_sfml.so";
        }
        return;
    }
    if (gfxLibs.size() != 0 && isGameSelected) {
        if (key == "Enter" && !isDisplaySelected) {
            std::string currentSelectedDisplay = gfxLibs[selectedDisplayIndex];
            _entities[currentSelectedDisplay].color_fg.red = 255;
            _entities[currentSelectedDisplay].color_fg.green = 0;
            _entities[currentSelectedDisplay].color_fg.blue = 0;
            _entities[currentSelectedDisplay].color_bg.red = 0;
            _entities[currentSelectedDisplay].color_bg.green = 0;
            _entities[currentSelectedDisplay].color_bg.blue = 0;
            isDisplaySelected = true;
            hasSelected = true;
            return;
        }
        if (key == "ESC" && isDisplaySelected) {
            std::string currentSelectedDisplay = gfxLibs[selectedDisplayIndex];
            _entities[currentSelectedDisplay].color_fg.red = 255;
            _entities[currentSelectedDisplay].color_fg.green = 255;
            _entities[currentSelectedDisplay].color_fg.blue = 255;
            _entities[currentSelectedDisplay].color_bg.red = 0;
            _entities[currentSelectedDisplay].color_bg.green = 0;
            _entities[currentSelectedDisplay].color_bg.blue = 0;
            isDisplaySelected = false;
            hasSelected = false;
            return;
        }
        if (key == "DownArrow" && !isDisplaySelected && (selectedDisplayIndex + 1) < gfxLibs.size()) {
            std::string currentSelectedDisplay = gfxLibs[selectedDisplayIndex];
            std::string newSelectedDisplay = gfxLibs[selectedDisplayIndex + 1];
            _entities[currentSelectedDisplay].underline = false;
            _entities[currentSelectedDisplay].bold = false;
            _entities[newSelectedDisplay].underline = true;
            _entities[newSelectedDisplay].bold = true;
            selectedDisplayIndex += 1;
            return;
        }
        if (key == "UpArrow" && !isDisplaySelected && selectedDisplayIndex != 0) {
            std::string currentSelectedDisplay = gfxLibs[selectedDisplayIndex];
            std::string newSelectedDisplay = gfxLibs[selectedDisplayIndex - 1];
            _entities[currentSelectedDisplay].underline = false;
            _entities[currentSelectedDisplay].bold = false;
            _entities[newSelectedDisplay].underline = true;
            _entities[newSelectedDisplay].bold = true;
            selectedDisplayIndex -= 1;
            return;
        }
    }
    if (gameLibs.size() != 0) {
        if (key == "Enter" && !isGameSelected) {
            std::string currentSelectedGame = gameLibs[selectedGameIndex];
            _entities[currentSelectedGame].color_fg.red = 255;
            _entities[currentSelectedGame].color_fg.green = 0;
            _entities[currentSelectedGame].color_fg.blue = 0;
            _entities[currentSelectedGame].color_bg.red = 0;
            _entities[currentSelectedGame].color_bg.green = 0;
            _entities[currentSelectedGame].color_bg.blue = 0;
            isGameSelected = true;
            return;
        }
        if (key == "ESC" && isGameSelected) {
            std::string currentSelectedGame = gameLibs[selectedGameIndex];
            _entities[currentSelectedGame].color_fg.red = 255;
            _entities[currentSelectedGame].color_fg.green = 255;
            _entities[currentSelectedGame].color_fg.blue = 255;
            _entities[currentSelectedGame].color_bg.red = 0;
            _entities[currentSelectedGame].color_bg.green = 0;
            _entities[currentSelectedGame].color_bg.blue = 0;
            isGameSelected = false;
            return;
        }
        if (key == "DownArrow" && !isGameSelected && (selectedGameIndex + 1) < gameLibs.size()) {
            std::string currentSelectedGame = gameLibs[selectedGameIndex];
            std::string newSelectedGame = gameLibs[selectedGameIndex + 1];
            _entities[currentSelectedGame].underline = false;
            _entities[currentSelectedGame].bold = false;
            _entities[newSelectedGame].underline = true;
            _entities[newSelectedGame].bold = true;
            selectedGameIndex += 1;
            return;
        }
        if (key == "UpArrow" && !isGameSelected && selectedGameIndex != 0) {
            std::string currentSelectedGame = gameLibs[selectedGameIndex];
            std::string newSelectedGame = gameLibs[selectedGameIndex - 1];
            _entities[currentSelectedGame].underline = false;
            _entities[currentSelectedGame].bold = false;
            _entities[newSelectedGame].underline = true;
            _entities[newSelectedGame].bold = true;
            selectedGameIndex -= 1;
            return;
        }
    }
}
