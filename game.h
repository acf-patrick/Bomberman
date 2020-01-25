#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "timer.h"
#include "vector.h"

class Game
{
private:
	SDL_Surface *screen, *start_s;
	bool running, at_start_s;
	Timer fps_t;

	void start();
	void regulate_FPS(); // juste nafindra tato ftsn lay codenla

public:
	Game();
	~Game();
	void run();
};

