#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "timer.h"
#include "vector.h"
#include "assetsmanager.h"

class Game
{
private:
	SDL_Surface *screen, *start_s, *stage_s; //napina surface iray mampiseho ilay numero anle stage
	bool running, at_start_s;
	int current_stage; //stage misy amzao
	Timer fps_t;
	AssetManager asset_Manager;

	void start();
	void play_stage();
	void regulate_FPS();

public:
	Game();
	~Game();
	void run();
};

