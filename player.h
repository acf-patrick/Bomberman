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
    Timer timer;
	bool dying;

    void updateFrame();

public:
	// ilaina amlay ref manan powerup izy ... dia static satria ho
	// modifien'i Bomb ary am destructor, ray ian raha teo ny
	// isan'ny player
	static int bombCnt;

	Player(MapManager*, int, int);

	void update() override final;
	void draw() override final;

	// ary am updateKeys an'i Game ty no antsoina
	// amzay ref mis SDL_KEYDOWN ian vao activé
	void dropBomb();
};
