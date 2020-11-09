#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "timer.h"
#include "vector.h"
#include "assetsmanager.h"
#include "map_manager.h"

class Game
{
private:
	SDL_Surface *screen, *start_s, *stage_s;
	bool running, at_start_s;
	int current_stage;
	Timer fps_t;
	AssetManager asset_Manager;
	Map_Manager map_manager;

	void start();
	void play_stage();
	void regulate_FPS();

public:
	Game();
	~Game();
	void run();
};

