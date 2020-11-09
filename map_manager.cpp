#include "map_manager.h"

Map_Manager::Map_Manager()
{
    srand(time(0));
	wall = asset_manager.load_surface("./data/images/wall.png", "wall");
	ground = asset_manager.load_surface("./data/images/ground.png", "ground");
    brick = asset_manager.load_surface("./data/images/brick.png", "brick");
    brick_count = 30; //isan ny biriky mety potika
}

Map_Manager::~Map_Manager()
{
	asset_manager.~AssetManager();
}

void Map_Manager::generate_map()
{
    for (int i=0; i<13; i++)
    {
        for (int j=0; j<30; j++)
        {
            if ((i %2 == 0 && j %2 == 0) || i == 0 || i == 12 || j == 0 || j == 29) //mamteka rindirna sy sol aloha
                map[i][j] = WALL;
            else map[i][j] = GROUND;
        }
    }
    while (brick_count > 0) //mametaka brick mety apoka randomly amin sol
    {
        int a,b;
        do
        {
            a = rand()%13; b = rand()%30;
        }
        while (map[a][b] != GROUND);
        map[a][b] = BRICK;
        brick_count--;
    }
}

void Map_Manager::show_map(SDL_Surface *screen)
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
