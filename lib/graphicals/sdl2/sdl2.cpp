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
    IMG_Init(0);
    _window = SDL_CreateWindow("Arcade - SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_SHOWN);
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    _font = TTF_OpenFont("font.ttf", 24);
}

void Sdl2::stop()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    TTF_CloseFont(_font);
    TTF_Quit();
    IMG_Quit();
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
    (void) entities;
    // for (auto const &entity : entities) {
    //     IGameModule::Entity e = entity.second;
    //     if (e.file_id > 0) {
    //         _image_surface = IMG_Load(e.file.c_str());
    //         _image_texture = SDL_CreateTextureFromSurface(_renderer, _image_surface);
    //         float x = (entity.second.x * 100) * 0.16;
    //         float y = (entity.second.y * 100) * 0.16;
    //         _image_rect = {(int)x, (int)y, _image_surface->w, _image_surface->h};
    //         SDL_FreeSurface(_image_surface);
    //         SDL_RenderCopy(_renderer, _image_texture, NULL, &_image_rect);
    //         continue;
    //     }
    //     if (entity.second.text.length()) {
    //         if (e.bold && e.underline) {
    //             TTF_SetFontStyle(_font, TTF_STYLE_BOLD | TTF_STYLE_UNDERLINE);
    //         }
    //         _text_surface = TTF_RenderText_Solid(_font, e.text.c_str(), {
    //             (Uint8)e.color_fg.red,
    //             (Uint8)e.color_fg.green,
    //             (Uint8)e.color_fg.blue, 255
    //         });
    //         _text_texture = SDL_CreateTextureFromSurface(_renderer, _text_surface);
    //         _text_rect = {(int)((entity.second.x * 100) * 0.16), (int)(entity.second.y * 100), _text_surface->w, _text_surface->h};
    //         SDL_FreeSurface(_text_surface);
    //         SDL_RenderCopy(_renderer, _text_texture, NULL, &_text_rect);
    //         TTF_SetFontStyle(_font, TTF_STYLE_NORMAL);
    //         continue;
    //     }
    // }
}

std::string Sdl2::getEvent()
{
    while (SDL_PollEvent(&_event)) {
        if (_event.type == SDL_QUIT) {
            return "close";
        }
        if (_event.type == SDL_KEYDOWN && _event.key.repeat == 0) {
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
                case SDLK_F1:
                    return "F1";
                case SDLK_F2:
                    return "F2";
                default:
                    return "";
            }
        }
        if (_event.type == SDL_TEXTINPUT && _event.key.repeat == 0) {
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

void Sdl2::saveTextures(const std::vector<std::string> &path_texture)
{
    (void)path_texture;
}
