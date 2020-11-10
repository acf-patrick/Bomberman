#pragma once

#include "map_manager.h"
#include "movable.h"
#include "vector.h"
#include "timer.h"
#include <SDL/SDL.h>

class Player : public Movable
{
private:
	Vector<float> velocity;

	SDL_Surface *spritesheet;
	/* amlay animation */
    Timer timer;
	/* ijerena anlay sprite tkn ho apesaina */
	bool dying;

    void updateFrame();

public:
	Player(MapManager*);

	void update();
	void draw(SDL_Surface*);
};
