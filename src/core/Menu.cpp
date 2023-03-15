/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-arcade-adam.elaoumari [WSL : Ubuntu]
** File description:
** Menu
*/

#include "Menu.hpp"

Menu::Menu(std::vector<std::string> gameLibs, std::vector<std::string> gfxLibs)
{
    float x = 0, y = 0;
    Entity gameEntity = {
        "",
        "Game Libs",
        "E9967A",
        "E9967A",
        x,
        y,
        true,
        true
    };
    y += 100;
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
            "E9967A",
            x,
            y,
            bold,
            underline,
        };
        entities.insert({val, gameLib});
        y += 100;
    }
    Entity gfxEntity = {
        "",
        "GFX Libs",
        "E9967A",
        "E9967A",
        x,
        y,
        true,
        true,
    };
    y += 100;
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
            "E9967A",
            x,
            y,
            bold,
            underline
        };
        entities.insert({val, gfxLib});
        y += 100;
    }
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
    if (key.empty() == false) {
        if (key == "close") {
            status = FINISHED;
        }
    }
}