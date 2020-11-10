#include "movable.h"
#include "vector.h"
#include "map_manager.h"

Movable::Movable(MapManager *m) : map(m)
{}

void Movable::move(int x, int y)
{
	/* rah ny tkn ho izy ts null zan fa aleo mailo */
	if (map == nullptr)
		GameObject::move(x, y);
    if (x >= PX or y >= PX)
	{
		move(x/2, y/2);
		move(x/2, y/2);
        return;
	}
    if (tryMove(x, y))
		return;
	affineMove(x, y);
}

bool Movable::tryMove(int x, int y)
{
	if (!map)
		return true;
    Vector<int> offset(x, y);
    position += offset;
    if (!map->checkCollision(this))
		return true;
    position -= offset;
    return false;
}

int abs(int z) { return z<0?-z:z; }
int sgn(int z) { return z?(z/abs(z)):0; }

void Movable::affineMove(int x, int y)
{
    for (int i = 0; i<abs(x); ++i)
		if (!tryMove(sgn(x), 0))
			break;
	for (int i = 0; i<abs(y); ++i)
		if (!tryMove(0, sgn(y)))
			break;
}
