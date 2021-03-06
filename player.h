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

    // rehefa lay mametraka bomb dia descativena
    // kely aloha ny collision fa mihitsoka ao lery
    GameObject *firstContact;

	int direction;
	int cur_frame;

	SDL_Surface *spritesheet;
    Timer timer;
	bool dying;

    void updateFrame();

public:

	Player(MapManager*, int, int);

	bool collide(GameObject&) override final;
	void update() override final;
	void draw() override final;

	// ary am updateKeys an'i Game ty no antsoina
	// amzay ref mis SDL_KEYDOWN ian vao activé
	void dropBomb();
};
