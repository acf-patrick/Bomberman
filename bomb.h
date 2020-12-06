#pragma once

#include "timer.h"
#include "group.h"
#include "object.h"
#include "vector.h"
#include "renderer.h"

class Bomb : public GameObject
{
private:
    SDL_Surface *sprite;
    int cur_frame;
    Timer timer, counter;

public:
	static int number;

    Bomb(int, int);

	void explode();

    void update() override final;
    void draw() override final;
};
