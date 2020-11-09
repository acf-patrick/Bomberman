#include "map_manager.h"
#include "assetsmanager.h"
#include <ctime>

Map_Manager::Map_Manager()
{
    srand(time(0));

    AssetManager &asset_manager = *AssetManager::instance;
	wall = asset_manager.load_surface("./data/images/wall.png", "wall");
	ground = asset_manager.load_surface("./data/images/ground.png", "ground");
    brick = asset_manager.load_surface("./data/images/brick.png", "brick");
    brick_count = 30;
}

Map_Manager::~Map_Manager()
{}

void Map_Manager::generate_map()
{
    for (int i=0; i<13; i++)
    {
        for (int j=0; j<30; j++)
        {
            if ((i %2 == 0 && j %2 == 0) || i == 0 || i == 12 || j == 0 || j == 29)
                map[i][j] = WALL;
            else map[i][j] = GROUND;
        }
    }
	for (int i=0;  i<brick_count; ++i)
    {
        int a,b;
        do
        {
            a = rand()%13;
            b = rand()%30;
        }
        while (map[a][b] != GROUND);
        map[a][b] = BRICK;
    }
}

void Map_Manager::draw(SDL_Surface *screen)
{
	for (int i=0; i<13;i++)
	{
		for (int j=0; j<30; j++)
		{
			pos.x = j * 32;
			pos.y = i * 32;
        	if (map[i][j] == GROUND)
            	SDL_BlitSurface(ground,NULL,screen,&pos);
        	else if (map[i][j] == WALL)
            	SDL_BlitSurface(wall,NULL,screen,&pos);
            else if (map[i][j] == BRICK)
            	SDL_BlitSurface(brick,NULL,screen,&pos);
		}
	}
}
