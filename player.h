#pragma once

#include "map_manager.h"
#include "movable.h"
#include "vector.h"
#include "timer.h"
#include "renderer.h"
#include "bomb.h"

class Player : public Movable
{
private:
    enum { UP, DOWN, LEFT, RIGHT };

	int direction;
	int cur_frame;

	SDL_Surface *spritesheet;
    Timer timer, bomb_drop;
	bool dying, dropped_bomb;

    void updateFrame();

public:
	Player(MapManager*, int, int);

	void update() override final;
	void draw() override final;
};
