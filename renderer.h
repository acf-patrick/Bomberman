#pragma once

#include <SDL/SDL.h>
#include "camera.h"

struct Renderer
{
	static SDL_Surface* screen;
	static Camera* camera;
};

SDL_Surface* Renderer::screen = nullptr;
Camera* Renderer::camera = nullptr;
