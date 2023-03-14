/*
** EPITECH PROJECT, 2023
** IGameModule.hpp
** File description:
** IGameModule
*/

#ifndef IGAME_MODULE
    #define IGAME_MODULE

#include <iostream>
#include <string>
#include <map>

class IGameModule {
    public:
        enum GAME_STATUS {
            MENU,
            PAUSED,
            IN_GAME,
            FINISHED
        };

        struct Entity {
            std::string file;
            std::string text;
            std::string color;
            std::string background_color;
            float x;
            float y;
            bool isSprite;
        };

        virtual ~IGameModule () = default ;
        virtual void startGame() = 0;
        virtual bool isGameOver() = 0;
        virtual void update(std::string key) = 0;
        virtual std::map<std::string, Entity> getInfos() = 0;
        virtual GAME_STATUS getGameStatus() = 0;

    protected:
    private:
};

#endif