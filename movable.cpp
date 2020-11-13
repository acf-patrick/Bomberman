#include "movable.h"
#include "vector.h"
#include "map_manager.h"

Movable::Movable(MapManager *m) : map(m)
{}

void Movable::move(float x, float y)
{
	if (map == nullptr)
		GameObject::move(x, y);
    Vector<float> offset(x, y);
    position += offset;
    if (!map->checkCollision(this))
		return;
    position -= offset;
}
