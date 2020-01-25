#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <map>

/* napiana géstion an'ny police koa */

class AssetManager
{
private:
	/* string no hiRepresentean ny ID dia iny ian koa ny key
	amlay "map" dia lay ressource ny value */
	std::map<std::string, SDL_Surface*> surfaces;
	std::map<std::string, TTF_Font*> fonts;
    std::map<std::string, Mix_Chunk*> chunks;
    std::map<std::string, Mix_Music*> musics;

    /* hiGenerena anlay ID raha toa ka ts manome param anreo method load */
    std::string getID(const char*);

public:
	static AssetManager *instance;

    AssetManager();
    ~AssetManager();

    SDL_Surface *load_surface(const char *file, std::string ID = "");
    TTF_Font *load_font(const char* file, std::size_t, std::string ID = "");
    Mix_Music *load_music(const char *file, std::string ID = "");
    Mix_Chunk *load_effect(const char *file, std::string ID = "");

    void play_music(Mix_Music *music, int value = 0);
    void play_music(std::string, int value = 0);

    void play_effect(Mix_Chunk *effect);
    void play_effect(std::string);

    /* getters : saho misy ilàna anlay ressources rehefa any aoriana any */
    SDL_Surface* get_surface(std::string);
    TTF_Font* get_font(std::string);
    Mix_Music* get_music(std::string);
    Mix_Chunk* get_chunk(std::string);
};

