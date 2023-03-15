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
#include <SDL2/SDL_ttf.h>

#include "IDisplay.hpp"

class Sdl2 : public IDisplayModule {
    public:
        Sdl2();
        ~Sdl2();
        void init();
        void stop();
        void draw();
        void update(std::map<std::string, IGameModule::Entity> entities);
        std::string getEvent();
        const std::string &getName() const;

    protected:
    private:
        SDL_Window *_window;
        SDL_Renderer *_renderer;
        SDL_Event _event;
        std::string _name = "SDL2";
        //text
        TTF_Font *_font;
        SDL_Texture *_text_texture = nullptr;
        SDL_Surface *_text_surface;
        SDL_Rect _text_rect;
};
