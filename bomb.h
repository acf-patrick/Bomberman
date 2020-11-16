#pragma once

#include "object.h"
#include "vector.h"
#include "timer.h"
#include "renderer.h"

class Bomb : public GameObject
{
private:
    SDL_Surface *sprite;
    int cur_frame;
    Timer timer;

public:
	static int number;

    Bomb(int, int);
	~Bomb() override final;

    void update() override final;
    void draw() override final;
};