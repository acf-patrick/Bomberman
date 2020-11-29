#include "assetsmanager.h"
#include <iostream>

AssetManager* AssetManager::instance = nullptr;

AssetManager::AssetManager()
{
    instance = this;

    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    TTF_Init();
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
}

AssetManager::~AssetManager()
{
    for (auto &item : surfaces)
        SDL_FreeSurface(item.second);
    for (auto &item : chunks)
        Mix_FreeChunk(item.second);
    for (auto &item : musics)
        Mix_FreeMusic(item.second);
    surfaces.clear();
    fonts.clear();
    chunks.clear();
    musics.clear();

    TTF_Quit();
    Mix_CloseAudio();
}

SDL_Surface *AssetManager::load_surface(const char *file, std::string ID)
{
    if (ID.empty())
        ID = getID(file);
    SDL_Surface* surface = IMG_Load(file);
    if (!surface)
    {
        std::cerr << IMG_GetError() << std::endl;
        return NULL;
    }
    return (surfaces[ID] = surface);
}

TTF_Font *AssetManager::load_font(const char *file, std::size_t char_size, std::string ID)
{
    if (ID.empty())
        ID = getID(file);
    TTF_Font* font = TTF_OpenFont(file, char_size);
    if (!font)
    {
        std::cerr << TTF_GetError() << std::endl;
        return NULL;
    }
   return (fonts[ID] = font);
}

Mix_Music *AssetManager::load_music(const char *file, std::string ID)
{
    if (ID.empty())
        ID = getID(file);
    Mix_Music* music = Mix_LoadMUS(file);
    if (!music)
    {
        std::cerr << Mix_GetError() << std::endl;
        return NULL;
    }
    return (musics[ID] = music);
}

Mix_Chunk *AssetManager::load_effect(const char *file, std::string ID)
{
    if (ID.empty())
        ID = getID(file);
    Mix_Chunk* chunk = Mix_LoadWAV(file);
    if (!chunk)
    {
        std::cerr << Mix_GetError() << std::endl;
        return NULL;
    }
    return (chunks[ID] = chunk);
}

void AssetManager::play_music(Mix_Music *music, int value)
{
    Mix_PlayMusic(music, value);
}

void AssetManager::play_music(std::string ID, int value)
{
    play_music(musics[ID], value);
}

void AssetManager::play_effect(Mix_Chunk *effect)
{
    Mix_PlayChannel(-1,effect,0);
}

void AssetManager::play_effect(std::string ID)
{
    play_effect(chunks[ID]);
}

SDL_Surface* AssetManager::get_surface(std::string ID)
{ return surfaces[ID]; }

Mix_Music* AssetManager::get_music(std::string ID)
{ return musics[ID]; }

Mix_Chunk* AssetManager::get_chunk(std::string ID)
{ return chunks[ID]; }

TTF_Font* AssetManager::get_font(std::string ID)
{ return fonts[ID]; }

std::string AssetManager::getID(const char *file_name)
{
    std::string file(file_name);
    int slash = file.find_last_of("/"),
        dot = file.find_last_of(".");
    return file.substr(slash+1, dot-(slash+1));
}
