#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "timer.h"
#include "vector.h"
#include "assetsmanager.h"

class Game
{
private:
	SDL_Surface *screen, *start_s;
	bool running, at_start_s;
	Timer fps_t;
	assetManager asset_Manager;
	Mix_Music *startscreen, *stagestart;

	void start();
	void regulate_FPS();

public:
	Game();
	~Game();
	void run();
};

