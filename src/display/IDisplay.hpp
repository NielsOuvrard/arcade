/*
** IDisplayModule
**  ________  ________  ________  ________  ________  _______
** |\   __  \|\   __  \|\   ____\|\   __  \|\   ___ \|\  ___ \
** \ \  \|\  \ \  \|\  \ \  \___|\ \  \|\  \ \  \_|\ \ \   __/|
**  \ \   __  \ \   _  _\ \  \    \ \   __  \ \  \ \\ \ \  \_|/__
**   \ \  \ \  \ \  \\  \\ \  \____\ \  \ \  \ \  \_\\ \ \  \_|\ \
**    \ \__\ \__\ \__\\ _\\ \_______\ \__\ \__\ \_______\ \_______\
**     \|__|\|__|\|__|\|__|\|_______|\|__|\|__|\|_______|\|_______|
**
*/

#ifndef DISPLAY_MODULE_I
    #define DISPLAY_MODULE_I

#include <string>
#include "../game/IGameModule.hpp"

class IDisplayModule {
    public:
        virtual ~IDisplayModule () = default ;
        virtual void init() = 0;
        virtual void stop() = 0;
        virtual void update(std::map<std::string, IGameModule::Entity> entities) = 0;
        virtual void draw() = 0;
        virtual std::string getEvent() = 0;
        virtual const std::string &getName() const = 0;
};

#endif /* !DISPLAY_MODULE_I */