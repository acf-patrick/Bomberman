#pragma once

#include "object.h"

class MapManager;

class Movable : public GameObject
{
protected:
	MapManager *map;

	void tryMove(float, float);

public:
	Movable(MapManager*);
	void move(float, float) override;
};
