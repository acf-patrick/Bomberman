#pragma once

#include "vector.h"
#include "defs.h"
#include "object.h"
#include <SDL/SDL.h>

class MapManager
{
private:
   enum { WALL,GROUND,BRICK } ;
   SDL_Surface *wall,*ground,*brick;
   int map[MAP_H][MAP_W];
   int brick_count;

public:
    MapManager();
    ~MapManager();

    void generate_map();

    bool checkCollision(GameObject*);

    void draw();
};
