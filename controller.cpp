#include "controller.h"
#include "renderer.h"

Controller::Controller(std::array<bool, SDLK_LAST> &k) :
	keys(k), assets(*AssetManager::instance)
{
	assets.load_surface("./data/images/buttons/dir.png");
	assets.load_surface("./data/images/buttons/a.png");
	assets.load_surface("./data/images/buttons/b.png");
}

void Controller::update()
{

}

void Controller::draw(SDL_Surface* screen)
{
    SDL_Rect pos;
	SDL_Surface* surf;

	surf = assets.get_surface("dir");
    pos.x = 15;
    pos.y = screen->h - (surf->h+15);
    SDL_BlitSurface(surf, NULL, screen, &pos);

    surf = assets.get_surface("b");
    pos.x = screen->w - (surf->w+15);
    pos.y = screen->h - (2*surf->h+20);
    SDL_BlitSurface(surf, NULL, screen, &pos);

    surf = assets.get_surface("a");
    pos.x -= (surf->w+5);
    pos.y += (surf->h+5);
	SDL_BlitSurface(surf, NULL, screen, &pos);
}
