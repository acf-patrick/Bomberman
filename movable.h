#pragma once

#include "object.h"

class MapManager;

class Movable : public GameObject
{
private:
	MapManager *map;

	bool tryMove(float, float);
	void affineMove(float, float);

public:
	Movable(MapManager*);
	void move(float, float) override;
};
