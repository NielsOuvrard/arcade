/*
**       _/_/_/  _/_/_/    _/          _/_/
**    _/        _/    _/  _/        _/    _/
**     _/_/    _/    _/  _/            _/
**        _/  _/    _/  _/          _/
** _/_/_/    _/_/_/    _/_/_/_/  _/_/_/_/
**
*/

#include "sdl2.hpp"

Sdl2::Sdl2()
{
    SDL_HideWindow(_window);
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    IMG_Init(0);
    _window = SDL_CreateWindow("Arcade - SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL);
}

Sdl2::~Sdl2()
{
    SDL_DestroyWindow(_window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Sdl2::init()
{
    SDL_ShowWindow(_window);
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    _font = TTF_OpenFont("font.ttf", 60);
    resetDisplay();
}

void Sdl2::stop()
{
    SDL_HideWindow(_window);
    TTF_CloseFont(_font);
    SDL_DestroyRenderer(_renderer);
}

void Sdl2::draw()
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderPresent(_renderer);
}

void Sdl2::update(std::map<std::string, IGameModule::Entity> entities)
{
    SDL_RenderClear(_renderer);
    _renderedTextures.clear();
    for (auto const &entity : entities) {
        IGameModule::Entity e = entity.second;
        if (e.id_file == -1) {
            if (e.bold && e.underline) {
                TTF_SetFontStyle(_font, TTF_STYLE_UNDERLINE);
            }
            _text_surface = TTF_RenderText_Solid(_font, e.text.c_str(), {
                (Uint8)e.color_fg.red,
                (Uint8)e.color_fg.green,
                (Uint8)e.color_fg.blue, 255
            });
            _text_texture = SDL_CreateTextureFromSurface(_renderer, _text_surface);
            _text_rect = {(int)((e.x * 100)), (int)(e.y * 100), _text_surface->w, _text_surface->h};
            SDL_FreeSurface(_text_surface);
            SDL_RenderCopy(_renderer, _text_texture, NULL, &_text_rect);
            _renderedTextures.insert(_renderedTextures.end(), _text_texture);
            TTF_SetFontStyle(_font, TTF_STYLE_NORMAL);
        } else {
            float x = (e.x * 100) * 0.16;
            float y = (e.y * 100) * 0.16;
            _rects[e.id_file].x = (int)x;
            _rects[e.id_file].y = (int)y;
            SDL_RenderCopy(_renderer, _textures[e.id_file], NULL, &_rects[e.id_file]);
        }
    }
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

void Sdl2::resetDisplay(void)
{
    _textures.clear();
    _rects.clear();
    _renderedTextures.clear();
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

void Sdl2::saveTextures(const std::vector<std::string> &texture)
{
    for (auto const &val : texture) {
        SDL_Surface *_image_surface;
        _image_surface = IMG_Load(val.c_str());
        SDL_Texture *_image_texture;
        _image_texture = SDL_CreateTextureFromSurface(_renderer, _image_surface);
        std::cout << "load texture: " << val << std::endl;
        _textures.push_back(_image_texture);
        _rects.push_back({0, 0, _image_surface->w, _image_surface->h});
        SDL_FreeSurface(_image_surface);
    }
}
