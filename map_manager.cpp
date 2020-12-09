#include "assetsmanager.h"
#include "map_manager.h"
#include "explosion.h"
#include "renderer.h"
#include "object.h"
#include "bomb.h"
#include <ctime>
#include <cstdlib>

MapManager::MapManager() :
	explosions(Explosion::group)
{
    srand(time(0));

    for (int i=0; i<MAP_H; ++i)
		for (int j=0; j<MAP_W; ++j)
			bombs_arr[i][j] = false;

    AssetManager &asset_manager = *AssetManager::instance;
	sprites[WALL] = asset_manager.load_surface("./data/images/wall.png");
    sprites[BRICK] = asset_manager.load_surface("./data/images/brick.png");
	sprites[GROUND] = asset_manager.load_surface("./data/images/ground.png");
    brick_count = 30;
}

MapManager::~MapManager()
{}

void MapManager::generate_map()
{
    map = (int**)malloc(MAP_H*sizeof (int*));
    for (int k=0; k<MAP_H; ++k)
		map[k] = (int*)malloc(MAP_W*sizeof (int));

    for (int i = 0; i < MAP_H; i++)
    {
        for (int j = 0; j < MAP_W; j++)
        {
            if ((i %2 == 0 and j %2 == 0) or i == 0 or i == 12 or j == 0 or j == 29)
                map[i][j] = WALL;
            else map[i][j] = GROUND;
        }
    }
	for (int i = 0;  i < brick_count; ++i)
    {
        int a, b;
        do
        {
            a = rand()%13;
            b = rand()%30;
        }
        while (map[a][b] != GROUND or (a==1 and b==2) or (a==2 and b==1) or (a==1 and b==1));
        map[a][b] = BRICK;
    }

    Explosion::map = map;
}

void MapManager::update()
{
	bombs.update();
	explosions.update();
}

void MapManager::draw()
{
	SDL_Rect viewport(Renderer::camera->getViewport()), pos;
    int xmin = viewport.y / PX, xmax = (viewport.y+viewport.h) / PX;
	int ymin = viewport.x / PX, ymax = (viewport.x+viewport.w) / PX;

	if (xmin < 0)
		xmin = 0;
	if (ymin < 0)
		ymin = 0;
	if (xmax >= MAP_H)
		xmax = MAP_H-1;
	if (ymax >= MAP_W)
		ymax = MAP_W-1;

	for (int i = xmin; i <= xmax; i++)
	{
		for (int j = ymin; j <= ymax; j++)
		{
			Vector<int> dest(Renderer::camera->convert(j*PX, i*PX));
			pos.x = dest.x;
			pos.y = dest.y;
			SDL_BlitSurface(sprites[map[i][j]], NULL, Renderer::screen, &pos);
		}
	}

	bombs.draw();
	explosions.draw();
}

bool MapManager::checkCollision(GameObject *object)
{
	/* collision between objects */

    if (bombs.firstObjectCollidingWith(*object))
        return true;

	/* collision between tiles and object */

	SDL_Rect pos(object->getBoundingBox());

    int xmin = pos.y / PX, xmax = (pos.y+pos.h-1) / PX;
    int ymin = pos.x / PX, ymax = (pos.x+pos.w-1) / PX;

	if ((xmin < 0 or ymin < 0) or (xmax >= MAP_H or ymax >= MAP_W))
		return true;

	for (int i = xmin; i <= xmax; i++)
		for (int j = ymin; j <= ymax; j++)
			if (map[i][j] != GROUND)
				return true;

	return false;
}

// params : coordonnées anlay case
GameObject* MapManager::addBomb(int x, int y)
{
	if (map[y][x] == GROUND or bombs_arr[y][x])
	{
		bombs_arr[y][x] = true;
		return bombs.create<Bomb>(x*PX, y*PX);
	}

	return nullptr;
}
