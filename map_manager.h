#pragma once

#include "vector.h"
#include <SDL/SDL.h>

class MapManager
{
private:
   enum { WALL,GROUND,BRICK } ;
   SDL_Surface *wall,*ground,*brick;
   SDL_Rect pos;
   int map[13][30], brick_count;

public:
    MapManager();
    ~MapManager();

    void generate_map();

    void draw(SDL_Surface *screen);
};
