#include "game.h"
#include "defs.h"
#include "camera.h"
#include "renderer.h"
#include <map>
#include <SDL/SDL_ttf.h>
#include <sstream>

std::array<bool, SDLK_LAST> Game::keys;

Game::Game()
{
    #ifdef __ANDROID__
        addJoystick = true;
    #else
        addJoystick = false;
    #endif

    SDL_Init(SDL_INIT_EVERYTHING);
    keys.fill(false);

    screen = SDL_SetVideoMode(addJoystick?800:WIDTH, HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    Renderer::screen = addJoystick?SDL_CreateRGBSurface(SDL_HWSURFACE, WIDTH, HEIGHT, 32, 0, 0, 0, 0):screen;
    controller = addJoystick?new Controller(keys):nullptr;

    player = new Player(&map_manager, PX+1, PX+1);

    Camera *c = new Camera(player);
    c->init({0, 0, WIDTH, HEIGHT});
    c->setLimit(MAP_W*PX, MAP_H*PX);
    Renderer::camera = c;

    start_s = asset_Manager.load_surface("./data/images/title.png");
    stage_s = asset_Manager.load_surface("./data/images/misc.png");

    asset_Manager.load_music("./data/sounds/music/titlescreen.mp3", "start screen");
    asset_Manager.load_music("./data/sounds/music/stagestart.mp3", "stage start");
    asset_Manager.load_music("./data/sounds/music/stageplay.mp3", "stage play");

    running = false;

    current_stage = 1;

    asset_Manager.load_font("./data/fonts/supercell.ttf", 20);
    Mix_VolumeMusic(0);
}

Game::~Game()
{
    delete player;
    player = nullptr;
    delete controller;
    controller = nullptr;
    asset_Manager.~AssetManager();
    Renderer::destroy();
    SDL_Quit();
}

void Game::run()
{
    start();
    stagePresentation();
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
    asset_Manager.play_music("start screen");
    while (true)
    {
        updateKeys();
        if (event.type == SDL_KEYDOWN)
            break;
        regulate_FPS();
        SDL_BlitSurface(start_s, NULL, Renderer::screen, &pos);
        SDL_Flip(Renderer::screen);
        drawScene();
    }
    fps_t.stop();
}

void Game::play_stage()
{
    fps_t.start();

    asset_Manager.play_music("stage start");
    SDL_Delay(3200);

    map_manager.generate_map();
    asset_Manager.play_music("stage play");

    while (true)
    {
        updateKeys();

        if (event.type == SDL_QUIT)
            break;

        if (addJoystick)
            controller->update();
        map_manager.update();
        player->update();
        Renderer::camera->update();
        regulate_FPS();

        map_manager.draw();
        player->draw();
        SDL_Flip(Renderer::screen);

        SDL_FillRect(screen, NULL, 0x0);
        if (addJoystick)
            controller->draw(screen);
        drawScene();
    }
}

void Game::stagePresentation()
{
    SDL_FillRect(Renderer::screen, NULL, 0x0);

    SDL_Rect blit_stage, pos_stage;
    blit_stage.x = 0 ; blit_stage.y = 0;
    blit_stage.w = 40; blit_stage.h = 8;
    pos_stage.y = HEIGHT/2 - blit_stage.h/2;
    pos_stage.x = WIDTH/2 - blit_stage.w/2;
    SDL_BlitSurface(stage_s, &blit_stage, Renderer::screen, &pos_stage);

    blit_stage.x = (current_stage - 1)*8;
    blit_stage.y = 8;
    blit_stage.w = 8;
    pos_stage.x += 45;
    SDL_BlitSurface(stage_s, &blit_stage, Renderer::screen, &pos_stage);
    SDL_Flip(Renderer::screen);
    drawScene();

}

void Game::updateKeys()
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_KEYDOWN)
        {
            keys[event.key.keysym.sym] = true;
            if (event.key.keysym.sym == SDLK_SPACE)
                player->dropBomb();
        }
        if (event.type == SDL_KEYUP)
            keys[event.key.keysym.sym] = false;
    }
}

void Game::drawScene()
{
    if (!addJoystick)
        return;

    SDL_Rect pos = {
        Sint16(0.5*(screen->w-Renderer::screen->w)),
        Sint16(0.5*(screen->h-Renderer::screen->h)),
        0, 0
    };
    SDL_BlitSurface(Renderer::screen, NULL, screen, &pos);
    std::stringstream ss;
    ss << "( " << event.motion.x << ", " << event.motion.y << " )";
    SDL_Surface *s = TTF_RenderText_Solid(asset_Manager.get_font("supercell"), ss.str().c_str(), { 255, 255, 255 });
    pos.x = 10;
    pos.y = 10;
    SDL_BlitSurface(s, NULL, screen, &pos);
    SDL_FreeSurface(s);
    SDL_Flip(screen);
}
