/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-arcade-adam.elaoumari [WSL : Ubuntu]
** File description:
** Menu
*/

#include "Menu.hpp"

Menu::Menu(std::vector<std::string> gameLibsVal, std::vector<std::string> gfxLibsVal)
{
    gameLibs = gameLibsVal;
    gfxLibs = gfxLibsVal;
    float x = 0, y = 0;
    Entity gameEntity = {
        "",
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
    entities.insert({"Game Libs", gameEntity});
    for (std::string val : gameLibs) {
        bool bold = false, underline = false;
        if (val == gameLibs.front()) {
            bold = true;
            underline = true;
        }
        Entity  gameLib = {
            "",
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
        entities.insert({val, gameLib});
        y += 1;
    }
    Entity gfxEntity = {
        "",
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
    entities.insert({"GFX Libs", gfxEntity});
    for (std::string val : gfxLibs) {
        bool bold = false, underline = false;
        if (val == gfxLibs.front()) {
            bold = true;
            underline = true;
        }
        Entity gfxLib = {
            "",
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
        entities.insert({val, gfxLib});
        y += 1;
    }
    Entity nameTitle = {
        "",
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
    entities.insert({"nameTitle", nameTitle});
}

Menu::~Menu()
{
}

bool Menu::isGameOver()
{
    if (status == FINISHED)
        return true;
    return false;
}

void Menu::update(std::string key)
{
    if (key.empty())
        return;
    if (key == "close") {
        status = FINISHED;
    }
    if (key == "Backspace" && name.length() > 18) {
        name.resize(name.length() - 1);
        entities["nameTitle"].text = name;
    }
    if (key.length() == 1 && name.size() != 32) {
        name = name.append(key);
        entities["nameTitle"].text = name;
        return;
    }
    if (key == "Enter" && isGameSelected && isDisplaySelected && name.length() > 19) {
        status = FINISHED;
        return;
    }
    if (gfxLibs.size() != 0 && isGameSelected) {
        if (key == "Enter" && !isDisplaySelected) {
            std::string currentSelectedDisplay = gfxLibs[selectedDisplayIndex];
            entities[currentSelectedDisplay].color_fg.red = 255;
            entities[currentSelectedDisplay].color_fg.green = 0;
            entities[currentSelectedDisplay].color_fg.blue = 0;
            entities[currentSelectedDisplay].color_bg.red = 0;
            entities[currentSelectedDisplay].color_bg.green = 0;
            entities[currentSelectedDisplay].color_bg.blue = 0;
            isDisplaySelected = true;
            hasSelected = true;
            return;
        }
        if (key == "ESC" && isDisplaySelected) {
            std::string currentSelectedDisplay = gfxLibs[selectedDisplayIndex];
            entities[currentSelectedDisplay].color_fg.red = 255;
            entities[currentSelectedDisplay].color_fg.green = 255;
            entities[currentSelectedDisplay].color_fg.blue = 255;
            entities[currentSelectedDisplay].color_bg.red = 0;
            entities[currentSelectedDisplay].color_bg.green = 0;
            entities[currentSelectedDisplay].color_bg.blue = 0;
            isDisplaySelected = false;
            hasSelected = false;
            return;
        }
        if (key == "DownArrow" && !isDisplaySelected && (selectedDisplayIndex + 1) < gfxLibs.size()) {
            std::string currentSelectedDisplay = gfxLibs[selectedDisplayIndex];
            std::string newSelectedDisplay = gfxLibs[selectedDisplayIndex + 1];
            entities[currentSelectedDisplay].underline = false;
            entities[currentSelectedDisplay].bold = false;
            entities[newSelectedDisplay].underline = true;
            entities[newSelectedDisplay].bold = true;
            selectedDisplayIndex += 1;
            return;
        }
        if (key == "UpArrow" && !isDisplaySelected && selectedDisplayIndex != 0) {
            std::string currentSelectedDisplay = gfxLibs[selectedDisplayIndex];
            std::string newSelectedDisplay = gfxLibs[selectedDisplayIndex - 1];
            entities[currentSelectedDisplay].underline = false;
            entities[currentSelectedDisplay].bold = false;
            entities[newSelectedDisplay].underline = true;
            entities[newSelectedDisplay].bold = true;
            selectedDisplayIndex -= 1;
            return;
        }
    }
    if (gameLibs.size() != 0) {
        if (key == "Enter" && !isGameSelected) {
            std::string currentSelectedGame = gameLibs[selectedGameIndex];
            entities[currentSelectedGame].color_fg.red = 255;
            entities[currentSelectedGame].color_fg.green = 0;
            entities[currentSelectedGame].color_fg.blue = 0;
            entities[currentSelectedGame].color_bg.red = 0;
            entities[currentSelectedGame].color_bg.green = 0;
            entities[currentSelectedGame].color_bg.blue = 0;
            isGameSelected = true;
            return;
        }
        if (key == "ESC" && isGameSelected) {
            std::string currentSelectedGame = gameLibs[selectedGameIndex];
            entities[currentSelectedGame].color_fg.red = 255;
            entities[currentSelectedGame].color_fg.green = 255;
            entities[currentSelectedGame].color_fg.blue = 255;
            entities[currentSelectedGame].color_bg.red = 0;
            entities[currentSelectedGame].color_bg.green = 0;
            entities[currentSelectedGame].color_bg.blue = 0;
            isGameSelected = false;
            return;
        }
        if (key == "DownArrow" && !isGameSelected && (selectedGameIndex + 1) < gameLibs.size()) {
            std::string currentSelectedGame = gameLibs[selectedGameIndex];
            std::string newSelectedGame = gameLibs[selectedGameIndex + 1];
            entities[currentSelectedGame].underline = false;
            entities[currentSelectedGame].bold = false;
            entities[newSelectedGame].underline = true;
            entities[newSelectedGame].bold = true;
            selectedGameIndex += 1;
            return;
        }
        if (key == "UpArrow" && !isGameSelected && selectedGameIndex != 0) {
            std::string currentSelectedGame = gameLibs[selectedGameIndex];
            std::string newSelectedGame = gameLibs[selectedGameIndex - 1];
            entities[currentSelectedGame].underline = false;
            entities[currentSelectedGame].bold = false;
            entities[newSelectedGame].underline = true;
            entities[newSelectedGame].bold = true;
            selectedGameIndex -= 1;
            return;
        }
    }
}
