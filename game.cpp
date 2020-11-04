#include "game.h"
#include "defs.h"

Game::Game()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    start_s = asset_Manager.load_surface("./data/images/title.png");
    stage_s = asset_Manager.load_surface("./data/images/misc.png");

    asset_Manager.load_music("./data/sounds/titlescreen.mp3", "start screen");
    asset_Manager.load_music("./data/sounds/stagestart.mp3", "stage start");

    running = false;
    at_start_s = true;

    current_stage = 1;
}

Game::~Game()
{
    asset_Manager.~AssetManager();
    SDL_Quit();
}

void Game::run()
{
    start();
    play_stage();
}

void Game::start()
{
    SDL_Rect pos;
    pos.x = 0.5*(WIDTH - start_s->w);
    pos.y = 0.5*(HEIGHT - start_s->h);

    fps_t.start();
    asset_Manager.play_music("start screen", -1);
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
    fps_t.stop();
}

void Game::regulate_FPS()
{
    int t = fps_t.get_elapsed_time();
    if (t < 1000/FPS)
        SDL_Delay(1000/FPS - t);
}

void Game::play_stage()
{
    fps_t.start();
    bool m_running = true;
    SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));
    SDL_Rect blit_stage, pos_stage;
    blit_stage.x = 0; blit_stage.y = 0;
    blit_stage.w = 40; blit_stage.h = 8;
    pos_stage.y = HEIGHT/2 - blit_stage.h/2;
    pos_stage.x = WIDTH/2 - blit_stage.w/2;
    SDL_BlitSurface(stage_s,&blit_stage,screen,&pos_stage);
    blit_stage.y = 8; blit_stage.x = (current_stage - 1)*8; //rehefa miova ny curr_stage dia mihisaka ilay nombre blitena
    blit_stage.w = 8;
    pos_stage.x += 45; //mihisaka kely hinlitena nale nombre
    SDL_BlitSurface(stage_s,&blit_stage,screen,&pos_stage);
    SDL_Flip(screen);
    asset_Manager.play_music("stage start", 1);
    while (m_running)
    {
        //asina anle zavtra mitanga in game amzay
        //ohatran mplante le screen vao kitihana tsy aiko hoe maninona na dia efa regule ary ny fpss
        regulate_FPS();
    }
}
