/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-arcade-adam.elaoumari
** File description:
** AGame
*/

#pragma once

#include "IGameModule.hpp"

class AGameModule : public IGameModule {
    public:
        enum DIRECTION {
            UP,
            DOWN,
            LEFT,
            RIGHT
        };
        AGameModule();
        ~AGameModule();
        void startGame();
        bool isGameOver();
        std::string getCurrentRuntimeGraphicDisplay() const;
        void setCurrentRuntimeGraphicDisplay(std::string currentRuntimeGraphicDisplay);
        GAME_STATUS getGameStatus() const;
        void setGameStatus(GAME_STATUS status);
        std::map<std::string, Entity> getInfos() const;
        void generateGrid(int lenght);
        std::vector<std::vector<int>> getGrid() const;
        void setGridValue(int y, int x, int value);
        void setNewEntity(std::string name, Entity entity);
        void updateEntity(std::string name, Entity entity);
        void clearEntities();
        DIRECTION getDirection() const;
        void setDirection(DIRECTION direction);

    protected:
        std::map<std::string, Entity> _entities;
        GAME_STATUS _status;
        std::string _currentRuntimeGraphicDisplay;
        DIRECTION _direction = DIRECTION::RIGHT;
        std::vector<std::vector<int>> _grid;

    private:
};
