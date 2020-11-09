#pragma once

#include "vector.h"
#include <SDL/SDL.h>

class Map_Manager
{
private:
   enum { WALL,GROUND,BRICK } ;
   SDL_Surface *wall,*ground,*brick;
   SDL_Rect pos;
   int map[13][30], brick_count;

public:
    Map_Manager();
    ~Map_Manager();

    void generate_map();

    void draw(SDL_Surface *screen);
};
