/*
** IGameModule
**  ________  ________  ________  ________  ________  _______
** |\   __  \|\   __  \|\   ____\|\   __  \|\   ___ \|\  ___ \
** \ \  \|\  \ \  \|\  \ \  \___|\ \  \|\  \ \  \_|\ \ \   __/|
**  \ \   __  \ \   _  _\ \  \    \ \   __  \ \  \ \\ \ \  \_|/__
**   \ \  \ \  \ \  \\  \\ \  \____\ \  \ \  \ \  \_\\ \ \  \_|\ \
**    \ \__\ \__\ \__\\ _\\ \_______\ \__\ \__\ \_______\ \_______\
**     \|__|\|__|\|__|\|__|\|_______|\|__|\|__|\|_______|\|_______|
**
*/

#ifndef IGAME_MODULE
    #define IGAME_MODULE

#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <chrono>
#include <memory>

typedef struct color_s {
    int red;
    int green;
    int blue;
} color_t;

class IGameModule {
    public:
        enum GAME_STATUS {
            MENU,
            PAUSED,
            IN_GAME,
            FINISHED
        };

        enum DIRECTION {
            UP,
            DOWN,
            LEFT,
            RIGHT
        };

        struct Entity {
            int id_file;
            std::string text;
            std::string background_color;
            float x;
            float y;
            bool underline;
            bool bold;
            color_t color_fg;
            color_t color_bg;
        };

        virtual ~IGameModule () = default;
        virtual void update(std::string key) = 0;
        virtual void startGame() = 0;
        virtual bool isGameOver() = 0;
        virtual std::vector<std::string> getTextures() = 0;
        virtual std::map<std::string, Entity> getInfos() const = 0;
        virtual GAME_STATUS getGameStatus() const = 0;
        virtual void setGameStatus(GAME_STATUS status) = 0;
        virtual void generateGrid(int lenght) = 0;
        virtual void generateGrid(std::vector<std::string>) = 0;
        virtual std::vector<std::vector<int>> getGrid() const = 0;
        virtual void setGridValue(int y, int x, int value) = 0;
        virtual void setNewEntity(std::string name, Entity entity) = 0;
        virtual void clearEntities() = 0;
        virtual DIRECTION getDirection() const = 0;
        virtual void setDirection(DIRECTION direction) = 0;
        virtual Entity &getEntity(std::string name) const = 0;
        virtual void setScore(int score) = 0;
        virtual void setText(std::string name, std::string text) = 0;
        virtual void setTime(int time) = 0;
        virtual const std::string &getName() const = 0;

    protected:
    private:
};

#endif