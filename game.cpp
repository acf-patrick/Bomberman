#include "game.h"
#include "defs.h"

Game::Game()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    /* ilay image unique nosaraako satria mbola hapiasa ttf ian sika rhf kelkel
       sad lay soratra ambany iny miovaova, otr high score iny? dia lay cursor
       koa mietsiketsika
     */
    start_s = asset_Manager.load_surface("./data/images/title.png");

    asset_Manager.load_music("./data/sounds/titlescreen.mp3", "start screen");
    asset_Manager.load_music("./data/sounds/stagestart.mp3", "stage start");

    running = false;
    at_start_s = true;
}

Game::~Game()
{
    asset_Manager.~AssetManager();
    SDL_Quit();
}

void Game::run()
{
    start();
}

void Game::start()
{
    SDL_Rect pos;
    pos.x = 0.5*(WIDTH - start_s->w);
    pos.y = 0.5*(HEIGHT - start_s->h);

    fps_t.start();
    asset_Manager.play_music("start screen");
    while (at_start_s)
    {
        SDL_Event event;
        SDL_BlitSurface(start_s, NULL, screen, &pos);
        SDL_Flip(screen);
        SDL_PollEvent(&event);
        if (event.type == SDL_KEYDOWN)
            at_start_s = false;
        regulate_FPS();
    }
}

void Game::regulate_FPS()
{
    int t = fps_t.get_elapsed_time();
    if (t < 1000/FPS)
        SDL_Delay(1000/FPS - t);
}
