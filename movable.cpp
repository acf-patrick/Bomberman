#include "movable.h"
#include "vector.h"
#include "map_manager.h"

Movable::Movable(MapManager *m) : map(m)
{}

void Movable::move(float x, float y)
{
	if (map == nullptr)
		GameObject::move(x, y);
    if (x >= PX or y >= PX)
	{
		move(x/2, y/2);
		move(x/2, y/2);
        return;
	}
    tryMove(x, y);
}

void Movable::tryMove(float x , float y)
{
	if (map == nullptr)
		return GameObject::move(x, y);
    Vector<float> offset(x, y);
    position += offset;
    if (map->checkCollision(this))
		position -= offset;
}
