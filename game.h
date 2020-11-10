#pragma once

#include <array>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "timer.h"
#include "vector.h"
#include "assetsmanager.h"
#include "map_manager.h"
#include "player.h"

class Game
{
private:
	AssetManager asset_Manager;
	MapManager map_manager;

	Player *player;
	/* itestena anlay scroll */
	GameObject fakePlayer;

	Timer fps_t;

	SDL_Surface *screen;
	SDL_Surface *start_s, *stage_s;

	SDL_Event event;

	/* ialana amlay SDL_EnableKeyRepeat */
	std::array<bool, SDLK_LAST> keys;
	bool running, at_start_s;
	int current_stage;

	/* lay mapseho anlay hoe stage firy 'sika zao */
	void stagePresentation();

	void start();
	void play_stage();
	void regulate_FPS();

	void updateKeys();

public:
	Game();
	~Game();

	void run();
};

