/*
**       _/_/_/  _/_/_/    _/          _/_/
**    _/        _/    _/  _/        _/    _/
**     _/_/    _/    _/  _/            _/
**        _/  _/    _/  _/          _/
** _/_/_/    _/_/_/    _/_/_/_/  _/_/_/_/
**
*/

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "IDisplayModule.hpp"

class Sdl2 : public IDisplayModule {
    public:
        Sdl2();
        ~Sdl2();
        void init();
        void stop();
        void draw();
        void update(std::map<std::string, IGameModule::Entity> entities);
        void saveTextures(const std::vector<std::string> &texture);
        std::string getEvent();
        const std::string &getName() const;
        void resetDisplay();
    protected:
    private:
        SDL_Window *_window = nullptr;
        SDL_Renderer *_renderer = nullptr;
        SDL_Event _event;
        std::string _name = "SDL2";
        //text
        TTF_Font *_font;
        SDL_Surface *_text_surface = nullptr;
        SDL_Rect _text_rect;
        //image
        //texture
        std::vector<SDL_Texture *> _textures;
        std::vector<SDL_Rect> _rects;
        std::vector<SDL_Texture *> _renderedTextures;
        Mix_Music *_music = nullptr;
};
