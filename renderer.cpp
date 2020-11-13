#include "renderer.h"

SDL_Surface* Renderer::screen = nullptr;
Camera* Renderer::camera = nullptr;

void Renderer::destroy()
{
    SDL_FreeSurface(screen);
    screen = nullptr;
    delete camera;
    camera = nullptr;
}
