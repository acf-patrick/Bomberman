#pragma once

#include "object.h"

class MapManager;

class Movable : public GameObject
{
private:
	MapManager *map;

public:
	Movable(MapManager*);
	void move(float, float) override;
};
