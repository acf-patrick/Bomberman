#pragma once

#include <array>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "timer.h"
#include "assetsmanager.h"
#include "map_manager.h"
#include "player.h"
#include "controller.h"

class Game
{
private:
	bool addJoystick;

	Controller *controller;

	AssetManager asset_Manager;
	MapManager map_manager;

	Player *player;

	Timer fps_t;

	SDL_Surface *screen;
	SDL_Surface *start_s, *stage_s;

	SDL_Event event;

	bool running, at_start_s;
	int current_stage;


	void start();
	void stagePresentation();
	void play_stage();
	void regulate_FPS();

	void updateKeys();

	void drawScene();

public:

	Game();
	~Game();

	void run();

	static std::array<bool, SDLK_LAST> keys;
};

