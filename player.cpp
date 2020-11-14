#include "game.h"
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
    blit_pos = { 0, 0, 16, 24 };
    dropped_bomb = false;
}

void Player::update()
{
/*    if (Game::keys[SDLK_SPACE])
    {
        //mametraka bombe (mdemarre anlme timer igerena ny cooldown)
		 if (bomb_drop.get_state() == Timer::STOPPED)
		 {
		 	bomb_drop.start();
		 	dropped_bomb = true;
		 	if (direction == UP)
				Bomb bomb(position.x, position.y - 31);
			else if (direction == DOWN)
				Bomb bomb(position.x, position.y + 31);
			else if (direction == LEFT)
				Bomb bomb(position.x -  31, position.y);
			else if (direction == RIGHT)
				Bomb bomb(position.x +  31, position.y);
		 }
    }*/
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
    if (Game::keys[SDLK_DOWN] || Game::keys[SDLK_UP] || Game::keys[SDLK_LEFT] || Game::keys[SDLK_RIGHT])
    {
        if (timer.get_state() == Timer::STOPPED)
            timer.start();
    }
}

void Player::draw()
{
    Vector<int> pos(Renderer::camera->convert(position.x, position.y));
    SDL_Rect tmp = {
        Sint16(pos.x), Sint16(pos.y),
        Uint16(size.x), Uint16(size.y)
    };
    switch (direction)
    {
	case DOWN:
		blit_pos.y = 0;
		break;
	case UP:
		blit_pos.y = 72;
		break;
	case RIGHT:
		blit_pos.y = 48;
		break;
	case LEFT:
		blit_pos.y = 25;
		break;
	default : ;
    }
    updateFrame();
    SDL_BlitSurface(spritesheet, &blit_pos, Renderer::screen, &tmp);
}

void Player::updateFrame()
{
    if (Game::keys[SDLK_DOWN] || Game::keys[SDLK_UP] || Game::keys[SDLK_LEFT] || Game::keys[SDLK_RIGHT])
    {
        if (timer.get_elapsed_time() > 100)
        {
            if (blit_pos.x < 96)
                blit_pos.x += 16;
            else
                blit_pos.x = 0;
            timer.stop();
        }
    }
    else if (!Game::keys[SDLK_SPACE])
	{
		blit_pos.x = 0;
		timer.stop();
	}
    if (dropped_bomb)
	{
		blit_pos.x = 112;
		dropped_bomb = false;
	}
	if (bomb_drop.get_elapsed_time() > 1500) //tokony ampiana condition mijery raha mbola misy bombe active kely eto
		bomb_drop.stop();						//rehefa implemente ny bombe
}
