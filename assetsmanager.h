#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

class assetManager
{
public:
    assetManager();
    ~assetManager();
    SDL_Surface *load_surface(const char *file); //mload surface
    Mix_Music *load_music(const char *file); //mload musique lavalava oh main theme
    Mix_Chunk *load_effect(const char *file); //mload effect sound madinika oh bombe mipoaka
    void unload_surface(SDL_Surface *surface); //reto mfree fotsiny rehefa mquit
    void unload_music(Mix_Music *music);
    void unload_effect(Mix_Chunk *effect);
    void play_music(Mix_Music *music, int value = 0); //value = 0 na 1 raha alefa indray ihany, -1 raha mloop indefiniment
    void play_effect(Mix_Chunk *effect); //mandefa anle effect indray ihany satria ny effect tsy dia misy dikany raha
                                             //miverina indefiniment
};
