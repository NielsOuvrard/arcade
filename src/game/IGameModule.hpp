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

typedef struct color_s {
    int red;
    int green;
    int blue;
} color_t;

typedef struct sprite_s {
    std::string path;
} sprite_t;

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
            std::string background_color;
            float x;
            float y;
            bool underline;
            bool bold;
            color_t color_fg;
            color_t color_bg;
            sprite_t sprite;
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