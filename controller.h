#pragma once

#include <SDL/SDL.h>
#include <array>
#include "assetsmanager.h"

class Controller
{
public:
    Controller(std::array<bool, SDLK_LAST>&);

    void update();
    void draw(SDL_Surface*);

	SDLKey getKey(int, int);

private:
    std::array<bool, SDLK_LAST> &keys;
    AssetManager &assets;
};
