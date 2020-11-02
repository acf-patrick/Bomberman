#include "game.h"
#include "defs.h"

Game::Game()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    start_s = asset_Manager.load_surface("./data/images/start_s.png");
    running = false;
    at_start_s = true;
}

Game::~Game()
{
    asset_Manager.unload_surface(screen);
    asset_Manager.unload_surface(start_s);
    asset_Manager.~assetManager();
    SDL_Quit();
}

void Game::run()
{
    start();
}

void Game::start()
{
    fps_t.start();
    while (at_start_s)
    {
        SDL_Event event;
        SDL_BlitSurface(start_s,NULL,screen,NULL);
        SDL_Flip(screen);
        SDL_PollEvent(&event);
        if (event.type == SDL_KEYDOWN)
            at_start_s = false; //ito mcontrole anle fps ho 6pfps sady tsy mampihinana cpu be
        regulate_FPS();
    }
}

void Game::regulate_FPS()
{
    int t = fps_t.get_elapsed_time();
    if (t < 1000/FPS)
        SDL_Delay(1000/FPS - t);
}
