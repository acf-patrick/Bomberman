#pragma once

#include "object.h"
#include "group.h"

class Explosion : public GameObject
{
public:
	static Group group;

	// lay paramètre fanarany halalana hoe firy case ny portée anlay explosion
	Explosion(int, int, int);

	void update() override final;
	void draw() override final;

private:
	SDL_Surface *spritesheet;

	int range;
};
