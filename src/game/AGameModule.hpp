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
        std::chrono::high_resolution_clock::time_point getChronoValue() const {return start;};
        void setChronoValue(std::chrono::high_resolution_clock::time_point val) { start = val;};
        std::chrono::duration<float> getTimeElapsed(std::chrono::high_resolution_clock::time_point clock) const;
        void setScore(int score) override;
        int getScore(void) const;
        void setText(std::string name, std::string text) override;
        int getTime(void) const;
        void setTime(int time) override;

    protected:
        mutable std::map<std::string, Entity> _entities;
        GAME_STATUS _status;
        DIRECTION _direction = DIRECTION::RIGHT;
        std::vector<std::vector<int>> _grid;
        int _score = 0;
        int _time = 0;
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
        std::chrono::high_resolution_clock::time_point scoreClock = std::chrono::high_resolution_clock::now();
    private:
};
