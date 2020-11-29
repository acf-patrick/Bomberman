#include "map_manager.h"
#include "assetsmanager.h"
#include "renderer.h"
#include "object.h"
#include "bomb.h"
#include <ctime>

MapManager::MapManager()
{
    srand(time(0));

    AssetManager &asset_manager = *AssetManager::instance;
	wall = asset_manager.load_surface("./data/images/wall.png");
	ground = asset_manager.load_surface("./data/images/ground.png");
    brick = asset_manager.load_surface("./data/images/brick.png");
    brick_count = 30;
}

MapManager::~MapManager()
{}

void MapManager::generate_map()
{
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
}

void MapManager::update()
{
	bombs.update();
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
			switch (map[i][j])
			{
			case GROUND:
            	SDL_BlitSurface(ground, NULL, Renderer::screen, &pos);
            	break;
			case WALL:
            	SDL_BlitSurface(wall, NULL, Renderer::screen, &pos);
				break;
			case BRICK:
            	SDL_BlitSurface(brick, NULL, Renderer::screen, &pos);
            	break;
			default : ;
			}
		}
	}

	bombs.draw();
}

bool MapManager::checkCollision(GameObject *object)
{
	/* collision between objects */

//    if (bombs.firstObjectCollidingWith(*object))
//        return true;

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
void MapManager::addBomb(int x, int y)
{
	for (auto& bomb : bombs)
		/* mCreer point kely dia jerena rah midona eo lay bomb */
		// efa mis bomb eo matoa midona
        if (bomb->collide({ x*PX+5, y*PX+5, 1, 1 }))
			return;

	if (map[y][x] == GROUND)
		bombs.create<Bomb>(x*PX, y*PX);
}
