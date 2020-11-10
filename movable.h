#pragma once

#include "object.h"

class MapManager;

class Movable : public GameObject
{
private:
	MapManager *map;

	/* checkena hoe afaka mikisika ve sa tsia
	raha afaka, dia andramana dia mreturn true*/
	bool tryMove(int, int);
	/* raha nikisaka be loatra izy dia tafatsofoka anaty
	rindrina ohatra dia corrigéna kely */
	void affineMove(int, int);

public:
	Movable(MapManager*);
	void move(int, int);
};
