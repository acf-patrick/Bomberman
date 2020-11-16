#include "defs.h"
#include "game.h"
#include "bomb.h"
#include "player.h"
#include "renderer.h"
#include "assetsmanager.h"

Player::Player(MapManager *m, int x, int y) :
    Movable(m), dying(false)
{
    position.setCartesian(x, y);
    size.setCartesian(16, 24);
    spritesheet = AssetManager::instance->load_surface("./data/images/spritesheet.png");
    direction = DOWN;
    cur_frame = 0;
}

void Player::dropBomb()
{
	// checkena hoe tsis bomb
	if (true or Bomb::number == 0)
	{
		// bomb : taille (size.y, size.y)
		int x, y;
		switch (direction)
		{
		case UP:
			x = position.x + 0.5*(size.x-size.y);
            y = position.y - size.y + 5;
            break;
		case DOWN:
			x = position.x + 0.5*(size.x-size.y);
            y = position.y + size.y;
            break;
		case RIGHT:
            x = position.x + size.x;
            y = position.y;
			break;
		case LEFT:
            x = position.x - size.y;
            y = position.y;
            break;
		default : ;
		}
        map->addBomb(x, y);
		cur_frame = 7;
	}
}

void Player::update()
{
	if (!Game::keys[SDLK_SPACE])
	{
		if (Game::keys[SDLK_UP])
		{
			move(0, -0.5);
			direction = UP;
		}
		if (Game::keys[SDLK_DOWN])
		{
			move(0,  0.5);
			direction = DOWN;
		}
		if (Game::keys[SDLK_LEFT])
		{
			move(-0.5, 0);
			direction = LEFT;
		}
		if (Game::keys[SDLK_RIGHT])
		{
			move( 0.5, 0);
			direction = RIGHT;
		}
	}

    updateFrame();
}

void Player::draw()
{
    Vector<int> pos(Renderer::camera->convert(position.x, position.y));
    // index : direction, value : indicen'lay ligne
    int bind[4] = { 3, 0, 1, 2 };
    SDL_Rect blit_pos, tmp;
    blit_pos = {
    	Sint16(cur_frame*size.x), Sint16(bind[direction]*size.y),
    	Uint16(size.x), Uint16(size.y)
	};
	tmp = { Sint16(pos.x), Sint16(pos.y) };
    SDL_BlitSurface(spritesheet, &blit_pos, Renderer::screen, &tmp);
}

void Player::updateFrame()
{
    if (!Game::keys[SDLK_SPACE])
	{
		if (Game::keys[SDLK_DOWN] || Game::keys[SDLK_UP] || Game::keys[SDLK_LEFT] || Game::keys[SDLK_RIGHT])
		{
			if (timer.get_elapsed_time() > 100)
			{
				cur_frame = (cur_frame+1)%7;
				timer.start();
			}
		}
		else
			cur_frame = 0;
	}
}
