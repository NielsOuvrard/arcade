/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-arcade-adam.elaoumari [WSL : Ubuntu]
** File description:
** Menu
*/

#include "Menu.hpp"

std::string getGameScore(std::string game_name)
{
    std::ifstream file("scores/" + game_name + ".txt");
    std::string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            return line;
        }
        file.close();
    }
    return "no points yet";
}

Menu::Menu(std::vector<std::string> gameLibsVal, std::vector<std::string> gfxLibsVal, std::string nameVal)
{
    _status = IN_GAME;
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
    int i = 0;
    for (std::string val : gfxLibs) {
        bool bold = false, underline = false;
        // if (val == gfxLibs.front()) {
        //     bold = true;
        //     underline = true;
        // }
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
        if (val == nameVal) {
            gfxLib.bold = true;
            gfxLib.underline = true;
            gfxLib.color_fg = {255, 0, 0};
            isDisplaySelected = true;
            hasSelected = true;
            selectedDisplayIndex = i;
        }
        setNewEntity(val, gfxLib);
        y += 1;
        i++;
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
    x = 12;
    y = 0;
    Entity scoreEntity = {
        -1,
        "High Scores",
        "E9967A",
        x,
        y,
        true,
        true,
        {255, 255, 255},
        {0, 0, 0}
    };
    setNewEntity("HighScores", scoreEntity);
    y += 1;
    for (std::string val : gameLibs) {
        std::string game_name = val.substr(11, val.length() - 14);
        std::string game_score = getGameScore(game_name);
        game_name[0] = toupper(game_name[0]);
        Entity score = {
            -1,
            game_name + ": " + game_score,
            "E9967A",
            x,
            y,
            false,
            false,
            {255, 255, 255},
            {0, 0, 0}
        };
        y += 1,
        setNewEntity("score" + std::to_string(y), score);
    }
}

Menu::~Menu()
{
}

void Menu::update(std::string key)
{
    if (key.empty())
        return;
    if (key == "close") {
        setGameStatus(CLOSED);
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
    // if (key.find("MouseLeft") != std::string::npos) {
    //     printf("Here\n");
    //     int x, y;
    //     sscanf(key.c_str(), "MouseLeft %d %d", &x, &y);
    //     for (std::string val : gameLibs) {
    //         int entityX = (getEntity(val).x * 100 * 0.16);
    //         int entityXL = (getEntity(val).x * 100 * 0.16) + (getEntity(val).text.length() * 100 * 0.16);
    //         int entityY = getEntity(val).y * 100 * 0.16;
    //         std::cout << val << std::endl;
    //         std::cout << ((x >= entityX && x <= entityXL) && (y >= entityY && y <= entityY + 100 * 0.16)) << std::endl;
    //         std::cout << "x: " << x << " y: " << y << std::endl;
    //         std::cout << "entityX: " << entityX << " entityXL: " << entityXL << std::endl;
    //         std::cout << "entityY: " << entityY << " entityYL: " << entityY + 100 * 0.16 << std::endl;
    //         if ((x >= entityX && x <= entityXL) && (y >= entityY && y <= entityY + 100 * 0.16)) {
    //             if (isGameSelected) {
    //                 std::string currentSelectedGame = gameLibs[selectedGameIndex];
    //                 color_t color_fg = {255, 255, 255};
    //                 color_t color_bg = {0, 0, 0};
    //                 getEntity(currentSelectedGame).color_fg = color_fg;
    //                 getEntity(currentSelectedGame).color_bg = color_bg;
    //             }
    //             selectedGameIndex = std::find(gameLibs.begin(), gameLibs.end(), val) - gameLibs.begin();
    //             color_t color_fg = {255, 0, 0};
    //             color_t color_bg = {0, 0, 0};
    //             getEntity(val).color_fg = color_fg;
    //             getEntity(val).color_bg = color_bg;
    //             isGameSelected = true;
    //         }
    //     }
    //     for (std::string val : gfxLibs) {
    //         if (x >= getEntity(val).x && x <= getEntity(val).x + getEntity(val).text.length() && y == getEntity(val).y) {
    //             if (isDisplaySelected) {
    //                 std::string currentSelectedDisplay = gfxLibs[selectedDisplayIndex];
    //                 color_t color_fg = {255, 255, 255};
    //                 color_t color_bg = {0, 0, 0};
    //                 getEntity(currentSelectedDisplay).color_fg = color_fg;
    //                 getEntity(currentSelectedDisplay).color_bg = color_bg;
    //             }
    //             selectedDisplayIndex = std::find(gfxLibs.begin(), gfxLibs.end(), val) - gfxLibs.begin();
    //             color_t color_fg = {255, 0, 0};
    //             color_t color_bg = {0, 0, 0};
    //             getEntity(val).color_fg = color_fg;
    //             getEntity(val).color_bg = color_bg;
    //             isDisplaySelected = true;
    //             return;
    //         }
    //     }
    // }
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
        if (key.starts_with("MouseClick")) { // pos = 0 limits the search to the prefix
            std::stringstream ss(key);
            std::string cmd;
            int x, y;
            ss >> cmd; // extract the command string "MouseClick"
            ss >> x >> y; // extract the integer values for x and y
            if (y >= gameLibs.size() + 2 && y < gameLibs.size() + 2 + gfxLibs.size()) {
                if (selectedDisplayIndex == y - gameLibs.size() - 2) {
                    std::string currentSelectedDisplay = gfxLibs[selectedDisplayIndex];
                    color_t color_fg = {255, 0, 0};
                    color_t color_bg = {0, 0, 0};
                    getEntity(currentSelectedDisplay).color_fg = color_fg;
                    getEntity(currentSelectedDisplay).color_bg = color_bg;
                    isDisplaySelected = true;
                    hasSelected = true;
                    return;
                }
                std::string currentSelectedDisplay = gfxLibs[selectedDisplayIndex];
                std::string newSelectedDisplay = gfxLibs[y - gameLibs.size() - 2];
                getEntity(currentSelectedDisplay).underline = false;
                getEntity(currentSelectedDisplay).bold = false;
                getEntity(newSelectedDisplay).underline = true;
                getEntity(newSelectedDisplay).bold = true;
                selectedDisplayIndex = y - gameLibs.size() - 2;
            }
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
        if (key.starts_with("MouseClick")) { // pos = 0 limits the search to the prefix
            std::stringstream ss(key);
            std::string cmd;
            int x, y;
            ss >> cmd; // extract the command string "MouseClick"
            ss >> x >> y; // extract the integer values for x and y
            if (y >= 1 && y <= gameLibs.size()) {
                if (selectedGameIndex == y - 1) {
                    std::string currentSelectedGame = gameLibs[selectedGameIndex];
                    color_t color_fg = {255, 0, 0};
                    color_t color_bg = {0, 0, 0};
                    getEntity(currentSelectedGame).color_fg = color_fg;
                    getEntity(currentSelectedGame).color_bg = color_bg;
                    isGameSelected = true;
                    return;
                }
                std::string currentSelectedGame = gameLibs[selectedGameIndex];
                std::string newSelectedGame = gameLibs[y - 1];
                getEntity(currentSelectedGame).underline = false;
                getEntity(currentSelectedGame).bold = false;
                getEntity(newSelectedGame).underline = true;
                getEntity(newSelectedGame).bold = true;
                selectedGameIndex = y - 1;
            }
            return;
        }
    }
}

void Menu::resetGame(void)
{
    
}