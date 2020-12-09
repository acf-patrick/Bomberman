#pragma once

#include "group.h"
#include "timer.h"
#include "object.h"

class Explosion : public GameObject
{
private:
	// rect iany ty fa lay méthode anaty GameObject no tena ilaina
	class Blast : public GameObject
	{
	public:
		Blast(int x, int y)
		{
			position.setCartesian(x*PX, y*PX);
			size.setCartesian(PX, PX);
		}
	};

	SDL_Surface *spritesheet, *surface[3];

	// hireglena ny rapidité anlay propagation
	const int dt;

	// ilaina amlay détection ana collision
	Group blast;

	int range, sens, state;

	Timer timer;

public:
	static Group* group;
	static int** map;

	// lay coordonnées, tonga dia coords ana case
	// lay paramètre fanarany halalana hoe firy case ny portée anlay explosion
	Explosion(int, int, int);

	void update() override final;
	void draw() override final;
	bool collide(GameObject&) override final;
};
