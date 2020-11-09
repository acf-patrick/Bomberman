#include "game.h"
#include "defs.h"
#include "camera.h"
#include "renderer.h"
#include <map>

Game::Game()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    keys.fill(false);

    Renderer::screen = screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    /* manarabody anlay perso lay camera */
    Camera *c = new Camera(&fakePlayer);
    c->init(SDL_Rect{0, 0, WIDTH, HEIGHT});
    c->setLimit(MAP_W*PX, MAP_H*PX);
    Renderer::camera = c;

    start_s = asset_Manager.load_surface("./data/images/title.png");
    stage_s = asset_Manager.load_surface("./data/images/misc.png");

    asset_Manager.load_music("./data/sounds/titlescreen.mp3", "start screen");
    asset_Manager.load_music("./data/sounds/stagestart.mp3", "stage start");
    asset_Manager.load_music("./data/sounds/stageplay.mp3", "stage play");

    running = false;

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

void Game::regulate_FPS()
{
    int t = fps_t.get_elapsed_time();
    if (t < 1000/FPS)
        SDL_Delay(1000/FPS - t);
}

void Game::start()
{
    SDL_Rect pos;
    pos.x = 0.5*(WIDTH - start_s->w);
    pos.y = 0.5*(HEIGHT - start_s->h);

    fps_t.start();
    asset_Manager.play_music("start screen", -1);
    while (true)
    {
        updateKeys();
        if (event.type == SDL_KEYDOWN)
            break;
        regulate_FPS();
        SDL_BlitSurface(start_s, NULL, screen, &pos);
        SDL_Flip(screen);
    }
    fps_t.stop();
}

void Game::play_stage()
{
    fps_t.start();

    stagePresentation();
    asset_Manager.play_music("stage start");
    SDL_Delay(3200);

    map_manager.generate_map();
    asset_Manager.play_music("stage play");

    while (true)
    {
        updateKeys();
        if (keys[SDLK_UP])
            fakePlayer.move(0, -1);
        if (keys[SDLK_DOWN])
            fakePlayer.move(0, 1);
        if (keys[SDLK_LEFT])
            fakePlayer.move(-1, 0);
        if (keys[SDLK_RIGHT])
            fakePlayer.move(1, 0);
        regulate_FPS();
        Renderer::camera->update();
        map_manager.draw();
        SDL_Flip(screen);
    }
}

void Game::stagePresentation()
{
    SDL_FillRect(screen, NULL, 0x0);

    SDL_Rect blit_stage, pos_stage;
    blit_stage.x = 0; blit_stage.y = 0;
    blit_stage.w = 40; blit_stage.h = 8;
    pos_stage.y = HEIGHT/2 - blit_stage.h/2;
    pos_stage.x = WIDTH/2 - blit_stage.w/2;
    SDL_BlitSurface(stage_s, &blit_stage, screen, &pos_stage);

    blit_stage.x = (current_stage - 1)*8;
    blit_stage.y = 8;
    blit_stage.w = 8;
    pos_stage.x += 45;
    SDL_BlitSurface(stage_s, &blit_stage, screen, &pos_stage);
    SDL_Flip(screen);
}

void Game::updateKeys()
{
    /* raha tsy atao boucle ty dia lasa zay event */
    /* volou ao amlay list d'evenement ian no voatest */
    /* raha sad nanetsika souris zan no nipotsitra touche */
    /* dia mety ts ho voaray lay event, nanindry touche */
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_KEYDOWN)
            keys[event.key.keysym.sym] = true;
        if (event.type == SDL_KEYUP)
            keys[event.key.keysym.sym] = false;
    }
}
