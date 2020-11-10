#include "player.h"
#include "assetsmanager.h"

Player::Player(MapManager *m) : Movable(m), dying(false)
{ spritesheet = AssetManager::instance->load_surface("spritesheet"); }

void Player::update()
{

}

void Player::updateFrame()
{

}
