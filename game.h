#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "timer.h"
#include "vector.h"
#include "assetsmanager.h"
#include "map_manager.h"
#include "renderer.h"
#include "player.h"

class Game
{
private:
	Renderer renderer;
	AssetManager asset_Manager;
	MapManager map_manager;
	Player player;
	Timer fps_t;
	SDL_Surface *start_s, *stage_s;
	bool running, at_start_s;
	int current_stage;

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

