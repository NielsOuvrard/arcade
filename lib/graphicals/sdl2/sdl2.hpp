/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-arcade-adam.elaoumari
** File description:
** sdl2
*/

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "../../../src/display/IDisplay.hpp"

class Sdl2 : public IDisplayModule {
    public:
        Sdl2();
        ~Sdl2();
        void init();
        void stop();
        void draw();

    protected:
    private:
        SDL_Window *_window;
        SDL_Renderer *_renderer;
        SDL_Event _event;
};
