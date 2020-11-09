#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "timer.h"
#include "vector.h"
#include "assetsmanager.h"
#include "map_manager.h"
#include "renderer.h"

class Game
{
private:
	Renderer renderer;
	SDL_Surface *screen, *start_s, *stage_s;
	bool running, at_start_s;
	int current_stage;
	Timer fps_t;
	AssetManager asset_Manager;
	Map_Manager map_manager;

	/* lay mapseho anlay hoe stage firy 'sika zao */
	void stagePresentation();

	void start();
	void play_stage();
	void regulate_FPS();

public:
	Game();
	~Game();
	void run();
};

