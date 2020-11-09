#pragma once

#include "vector.h"
#include "defs.h"
#include <SDL/SDL.h>

class MapManager
{
private:
   enum { WALL,GROUND,BRICK } ;
   SDL_Surface *wall,*ground,*brick;
   SDL_Rect pos;
   int map[MAP_H][MAP_W];
   int brick_count;

public:
    MapManager();
    ~MapManager();

    void generate_map();

    void draw();
};
