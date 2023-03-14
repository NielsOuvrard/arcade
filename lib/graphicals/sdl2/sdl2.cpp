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
    _window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
}

void Sdl2::stop()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void Sdl2::draw()
{
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
    SDL_RenderPresent(_renderer);
    SDL_Delay(1000/60);
}

void Sdl2::update(std::map<std::string, IGameModule::Entity> entities)
{
    if (entities.size() == 0) {
        return;
    }
    if (entities.find("close") != entities.end()) {
        std::cout << "close" << std::endl;
        return;
    }
}

std::string Sdl2::getEvent()
{
    while (SDL_PollEvent(&_event)) {
        if (_event.key.keysym.sym == SDLK_e) {
            return "e";
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
