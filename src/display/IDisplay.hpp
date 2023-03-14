/*
** EPITECH PROJECT, 2023
** IDisplayModule.hpp
** File description:
** IDisplayModule
*/

#ifndef DISPLAY_MODULE_I
    #define DISPLAY_MODULE_I

#include <string>
#include "../src/game/IGameModule.hpp"

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