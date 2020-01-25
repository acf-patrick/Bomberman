#include "assetsmanager.h"

assetManager::assetManager()
{
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
}

assetManager::~assetManager()
{
    Mix_CloseAudio();
}

SDL_Surface *assetManager::load_surface(const char *file)
{
    return IMG_Load(file);
}

Mix_Music *assetManager::load_music(const char *file)
{
    return Mix_LoadMUS(file);
}

Mix_Chunk *assetManager::load_effect(const char *file)
{
    return Mix_LoadWAV(file);
}

void assetManager::play_music(Mix_Music *music, int value)
{
    Mix_PlayMusic(music, value);
}

void assetManager::play_effect(Mix_Chunk *effect)
{
    Mix_PlayChannel(-1,effect,0);
}

void assetManager::unload_surface(SDL_Surface *surface)
{
    SDL_FreeSurface(surface);
}

void assetManager::unload_music(Mix_Music *music)
{
    Mix_FreeMusic(music);
}

void assetManager::unload_effect(Mix_Chunk *effect)
{
    Mix_FreeChunk(effect);
}
