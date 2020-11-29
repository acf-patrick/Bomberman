#pragma once

#include "group.h"
#include "timer.h"
#include "object.h"

class Explosion : public GameObject
{
private:
	SDL_Surface *spritesheet;

	int range;

	Timer timer;

public:
	static Group group;

	// lay paramètre fanarany halalana hoe firy case ny portée anlay explosion
	Explosion(int, int, int);

	void update() override final;
	void draw() override final;
};
