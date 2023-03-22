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
        {255, 255, 255},
        {0, 0, 0}
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
            {255, 255, 255},
            {0, 0, 0}
        };
        setNewEntity(val, gameLib);
        y += 1;
    }
    Entity gfxEntity = {
        -1,
        "GFX Libs",
        "E9967A",
        x,
        y,
        true,
        true,
        {255, 255, 255},
        {0, 0, 0}
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
            {255, 255, 255},
            {0, 0, 0}
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
        {255, 255, 255},
        {0, 0, 0}
    };
    setNewEntity("nameTitle", nameTitle);
    x += 1;

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
        getEntity("nameTitle").text = name;
        return;
    }
    if (key.length() == 1 && name.size() != 32) {
        name = name.append(key);
        getEntity("nameTitle").text = name;
        return;
    }
    if (key == "Enter" && isGameSelected && isDisplaySelected && name.length() > 19) {
        setGameStatus(FINISHED);
        return;
    }
    if (key == "F1") {
        if (getCurrentRuntimeGraphicDisplay() == "lib/arcade_sfml.so") {
            setCurrentRuntimeGraphicDisplay("lib/arcade_sdl2.so");
        } else if (getCurrentRuntimeGraphicDisplay() == "lib/arcade_sdl2.so") {
            setCurrentRuntimeGraphicDisplay("lib/arcade_ncurses.so");
        } else {
            setCurrentRuntimeGraphicDisplay("lib/arcade_sfml.so");
        }
        return;
    }
    if (gfxLibs.size() != 0 && isGameSelected) {
        if (key == "Enter" && !isDisplaySelected) {
            std::string currentSelectedDisplay = gfxLibs[selectedDisplayIndex];
            color_t color_fg = {255, 0, 0};
            color_t color_bg = {0, 0, 0};
            getEntity(currentSelectedDisplay).color_fg = color_fg;
            getEntity(currentSelectedDisplay).color_bg = color_bg;
            isDisplaySelected = true;
            hasSelected = true;
            return;
        }
        if (key == "ESC" && isDisplaySelected) {
            std::string currentSelectedDisplay = gfxLibs[selectedDisplayIndex];
            color_t color_fg = {255, 255, 255};
            color_t color_bg = {0, 0, 0};
            getEntity(currentSelectedDisplay).color_fg = color_fg;
            getEntity(currentSelectedDisplay).color_bg = color_bg;
            isDisplaySelected = false;
            hasSelected = false;
            return;
        }
        if (key == "DownArrow" && !isDisplaySelected && (selectedDisplayIndex + 1) < gfxLibs.size()) {
            std::string currentSelectedDisplay = gfxLibs[selectedDisplayIndex];
            std::string newSelectedDisplay = gfxLibs[selectedDisplayIndex + 1];
            getEntity(currentSelectedDisplay).underline = false;
            getEntity(currentSelectedDisplay).bold = false;
            getEntity(newSelectedDisplay).underline = true;
            getEntity(newSelectedDisplay).bold = true;
            selectedDisplayIndex += 1;
            return;
        }
        if (key == "UpArrow" && !isDisplaySelected && selectedDisplayIndex != 0) {
            std::string currentSelectedDisplay = gfxLibs[selectedDisplayIndex];
            std::string newSelectedDisplay = gfxLibs[selectedDisplayIndex - 1];
            getEntity(currentSelectedDisplay).underline = false;
            getEntity(currentSelectedDisplay).bold = false;
            getEntity(newSelectedDisplay).underline = true;
            getEntity(newSelectedDisplay).bold = true;
            selectedDisplayIndex -= 1;
            return;
        }
    }
    if (gameLibs.size() != 0) {
        if (key == "Enter" && !isGameSelected) {
            std::string currentSelectedGame = gameLibs[selectedGameIndex];
            color_t color_fg = {255, 0, 0};
            color_t color_bg = {0, 0, 0};
            getEntity(currentSelectedGame).color_fg = color_fg;
            getEntity(currentSelectedGame).color_bg = color_bg;
            isGameSelected = true;
            return;
        }
        if (key == "ESC" && isGameSelected) {
            std::string currentSelectedGame = gameLibs[selectedGameIndex];
            color_t color_fg = {255, 255, 255};
            color_t color_bg = {0, 0, 0};
            getEntity(currentSelectedGame).color_fg = color_fg;
            getEntity(currentSelectedGame).color_bg = color_bg;
            isGameSelected = false;
            return;
        }
        if (key == "DownArrow" && !isGameSelected && (selectedGameIndex + 1) < gameLibs.size()) {
            std::string currentSelectedGame = gameLibs[selectedGameIndex];
            std::string newSelectedGame = gameLibs[selectedGameIndex + 1];
            getEntity(currentSelectedGame).underline = false;
            getEntity(currentSelectedGame).bold = false;
            getEntity(newSelectedGame).underline = true;
            getEntity(newSelectedGame).bold = true;
            selectedGameIndex += 1;
            return;
        }
        if (key == "UpArrow" && !isGameSelected && selectedGameIndex != 0) {
            std::string currentSelectedGame = gameLibs[selectedGameIndex];
            std::string newSelectedGame = gameLibs[selectedGameIndex - 1];
            getEntity(currentSelectedGame).underline = false;
            getEntity(currentSelectedGame).bold = false;
            getEntity(newSelectedGame).underline = true;
            getEntity(newSelectedGame).bold = true;
            selectedGameIndex -= 1;
            return;
        }
    }
}
