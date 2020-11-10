#include "game.h"
#include "player.h"
#include "renderer.h"
#include "assetsmanager.h"

Player::Player(MapManager *m, int x, int y) :
	Movable(m), dying(false)
{
	position.setCartesian(x, y);
	size.setCartesian(31, 31);
}

void Player::update()
{
    if (Game::keys[SDLK_UP])
		move(0, -1);
	if (Game::keys[SDLK_DOWN])
		move(0,  1);
	if (Game::keys[SDLK_LEFT])
		move(-1, 0);
	if (Game::keys[SDLK_RIGHT])
		move( 1, 0);
}

/* niandry anlay sprites */
void Player::draw()
{
	Vector<int> pos(Renderer::camera->convert(position.x, position.y));
	/* mankaleo b lay warning dia aleo castena */
	SDL_Rect tmp = {
        Sint16(pos.x), Sint16(pos.y),
        Uint16(size.x), Uint16(size.y)
	};
	SDL_FillRect(Renderer::screen, &tmp, 0x0);
}

void Player::updateFrame()
{

}
