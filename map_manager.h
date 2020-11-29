#pragma once

#include "vector.h"
#include "defs.h"
#include "group.h"
#include <SDL/SDL.h>

class GameObject;

class MapManager
{
private:
   enum { WALL, GROUND, BRICK };

   SDL_Surface *wall,*ground,*brick;

   int map[MAP_H][MAP_W];
   int brick_count;

   Group bombs;

public:
    MapManager();
    ~MapManager();

    void generate_map();

    bool checkCollision(GameObject*);

    void addBomb(int, int);

    void update();
    void draw();
};
