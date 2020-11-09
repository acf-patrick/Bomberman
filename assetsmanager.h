#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <map>


class AssetManager
{
private:

	std::map<std::string, SDL_Surface*> surfaces;
	std::map<std::string, TTF_Font*> fonts;
    std::map<std::string, Mix_Chunk*> chunks;
    std::map<std::string, Mix_Music*> musics;

    std::string getID(const char*);

public:
	static AssetManager *instance;

    AssetManager();
    ~AssetManager();

    SDL_Surface *load_surface(const char *file, std::string ID = "");
    TTF_Font *load_font(const char* file, std::size_t, std::string ID = "");
    Mix_Music *load_music(const char *file, std::string ID = "");
    Mix_Chunk *load_effect(const char *file, std::string ID = "");

    void play_music(Mix_Music *music, int value = -1);
    void play_music(std::string, int value = -1);

    void play_effect(Mix_Chunk *effect);
    void play_effect(std::string);

    SDL_Surface* get_surface(std::string);
    TTF_Font* get_font(std::string);
    Mix_Music* get_music(std::string);
    Mix_Chunk* get_chunk(std::string);
};

