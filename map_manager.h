#pragma once

#include "vector.h"
#include "assetsmanager.h"
#include <SDL/SDL.h>
#include <fstream>
#include <ctime>

using namespace std;

class Map_Manager
{
private:
   enum {WALL,GROUND,BRICK} ;
   SDL_Surface *wall,*ground,*brick;
   SDL_Rect pos;
   int map[13][30], brick_count; //isan ny biriky mety potika
   AssetManager asset_manager;
public:
    Map_Manager();
    ~Map_Manager();
    void generate_map();
    void show_map(SDL_Surface *screen);
};
