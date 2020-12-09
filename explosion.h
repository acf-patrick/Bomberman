#pragma once

#include "group.h"
#include "timer.h"
#include "object.h"

class Explosion : public GameObject
{
private:
	SDL_Surface *spritesheet, *surface[3];

	// hireglena ny rapidité anlay propagation
	const int dt;

	int range, sens, state;

	Timer timer;

public:
	static Group group;
	static int **map;

	// lay coordonnées, tonga dia coords ana case
	// lay paramètre fanarany halalana hoe firy case ny portée anlay explosion
	Explosion(int, int, int);

	void update() override final;
	void draw() override final;
	bool collide(const GameObject&) const override final;
};
