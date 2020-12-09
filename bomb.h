#pragma once

#include "defs.h"
#include "timer.h"
#include "group.h"
#include "object.h"
#include "vector.h"
#include "renderer.h"
#include "map_manager.h"

class Bomb : public GameObject
{
private:
    SDL_Surface *sprite;
    int cur_frame;
    Timer timer, counter;

    MapManager &map;

public:
    static bool array[MAP_H][MAP_W];

	static int number;

    Bomb(int, int, MapManager*);

	void explode();

    void update() override final;
    void draw() override final;
};
