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
        AGameModule();
        ~AGameModule();
        void startGame() override;
        bool isGameOver() override;
        std::string getCurrentRuntimeGraphicDisplay() const override;
        void setCurrentRuntimeGraphicDisplay(std::string currentRuntimeGraphicDisplay) override;
        GAME_STATUS getGameStatus() const override;
        void setGameStatus(GAME_STATUS status) override;
        std::map<std::string, Entity> getInfos() const override;
        void generateGrid(int lenght) override;
        void generateGrid(std::vector<std::string>) override;
        std::vector<std::vector<int>> getGrid() const override;
        void setGridValue(int y, int x, int value) override;
        void setNewEntity(std::string name, Entity entity) override;
        void clearEntities() override;
        DIRECTION getDirection() const override;
        void setDirection(DIRECTION direction) override;
        Entity &getEntity(std::string name) const override;
        std::chrono::system_clock::time_point getChronoValue() const {return start;};
        void setChronoValue(std::chrono::system_clock::time_point val) { start = val;};
        std::chrono::duration<float> getTimeElapsed(void) const;
    protected:
        mutable std::map<std::string, Entity> _entities;
        GAME_STATUS _status;
        std::string _currentRuntimeGraphicDisplay;
        DIRECTION _direction = DIRECTION::RIGHT;
        std::vector<std::vector<int>> _grid;
        std::chrono::system_clock::time_point start = std::chrono::high_resolution_clock::now();
    private:
};
