#pragma once

#include "vector.h"
#include "defs.h"
#include "group.h"
#include <SDL/SDL.h>

class GameObject;

class MapManager
{
private:

   SDL_Surface *sprites[3];

   int **map;
   int brick_count;

   bool bombs_arr[MAP_H][MAP_W];

   Group bombs, &explosions;

public:
    MapManager();
    ~MapManager();

    void generate_map();

    bool checkCollision(GameObject*);

    GameObject* addBomb(int, int);

    void update();
    void draw();
};
