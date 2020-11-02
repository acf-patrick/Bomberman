#include "game.h"

Game::Game()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    start_s = IMG_Load("./data/images/start_s.png"); //ito ilay ecran titre, tokony atao sprite maromaro amzay maivana le image
    running = false;
    at_start_s = true;
}

Game::~Game()
{
    SDL_FreeSurface(screen);
    SDL_FreeSurface(start_s);
    SDL_Quit();
}

void Game::run()
{
    start(); //mlance ecran titre fotsiny ito
}

void Game::start()
{
    start_t.start();
    while (at_start_s)
    {
        SDL_Event event;
        SDL_BlitSurface(start_s,NULL,screen,NULL);
        SDL_Flip(screen);
        SDL_PollEvent(&event);
        if (event.type == SDL_KEYDOWN)
            at_start_s = false;
            //mbola tsisy choix fa rehefa mikitika touche dia tapitra 
        if (start_t.get_time() < 1000/FPS)
            SDL_Delay(1000/FPS - start_t.get_time()); //ito mcontrole anle fps ho 6pfps sady tsy mampihinana cpu be
    }
}


