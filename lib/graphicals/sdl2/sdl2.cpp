/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-arcade-adam.elaoumari
** File description:
** sdl2
*/

#include "sdl2.hpp"

Sdl2::Sdl2()
{
}

Sdl2::~Sdl2()
{
}

void Sdl2::init()
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    _window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    _font = TTF_OpenFont("font.ttf", 24);
}

void Sdl2::stop()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    TTF_CloseFont(_font);
    TTF_Quit();
    SDL_Quit();
}

void Sdl2::draw()
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderPresent(_renderer);
    SDL_Delay(1000/60);
}

void Sdl2::update(std::map<std::string, IGameModule::Entity> entities)
{
    SDL_RenderClear(_renderer);
    for (auto const &entity : entities) {
        if (entity.second.text.length()) {
            IGameModule::Entity e = entity.second;
            if (e.bold && e.underline) {
                TTF_SetFontStyle(_font, TTF_STYLE_BOLD | TTF_STYLE_UNDERLINE);
            }
            _text_surface = TTF_RenderText_Solid(_font, e.text.c_str(), {
                (Uint8)e.color_fg.red,
                (Uint8)e.color_fg.green,
                (Uint8)e.color_fg.blue, 255
            });
            _text_texture = SDL_CreateTextureFromSurface(_renderer, _text_surface);
            _text_rect = {(int)entity.second.x, (int)(entity.second.y * 100), _text_surface->w, _text_surface->h};
            SDL_FreeSurface(_text_surface);
            SDL_RenderCopy(_renderer, _text_texture, NULL, &_text_rect);
            TTF_SetFontStyle(_font, TTF_STYLE_NORMAL);
        }
    }
}

std::string Sdl2::getEvent()
{
    while (SDL_PollEvent(&_event)) {
        if (_event.type == SDL_QUIT) {
            return "close";
        }
        if (_event.type == SDL_KEYDOWN) {
            switch (_event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    return "close";
                case SDLK_RETURN:
                    return "Enter";
                case SDLK_LEFT:
                    return "LeftArrow";
                case SDLK_RIGHT:
                    return "RightArrow";
                case SDLK_UP:
                    return "UpArrow";
                case SDLK_DOWN:
                    return "DownArrow";
                case SDLK_BACKSPACE:
                    return "Backspace";
                default:
                    return "";
            }
        }
        if (_event.type == SDL_TEXTINPUT) {
            std::string val = _event.text.text;
            return val;
        }
    }
    return "";
}

const std::string &Sdl2::getName() const
{
    return _name;
}

extern "C" IDisplayModule *create(void)
{
    return new  Sdl2();
}

extern "C" std::string getType(void)
{
    return "Graphic";
}

extern "C" void destroy(IDisplayModule* obj) {
    delete obj;
}
