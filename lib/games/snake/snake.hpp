/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-arcade-adam.elaoumari
** File description:
** snake
*/

#pragma once

#include "IGameModule.hpp"

class Snake : public IGameModule {
    public:
        Snake();
        ~Snake();
        void startGame() {
            _gameStatus = IN_GAME;
        };
        bool isGameOver();
        void update(std::string key);
        std::string getEvent();
        const std::string &getName() const;
        GAME_STATUS getGameStatus();
        std::map<std::string, Entity> getInfos();
    protected:
    private:
        std::string _name = "Snake";
        std::map<std::string, IGameModule::Entity> _entities;
        IGameModule::GAME_STATUS _gameStatus = IGameModule::MENU;
        std::string _event = "";
        std::vector<std::vector<int>> _grid;
};
