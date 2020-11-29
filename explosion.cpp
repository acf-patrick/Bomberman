#include "renderer.h"
#include "explosion.h"
#include "assetsmanager.h"

Explosion::Explosion(int x, int y, int portee)
{
	range = portee;
	spritesheet = AssetManager::instance->get_surface("explosion");
	if (!spritesheet)
		spritesheet = AssetManager::instance->load_surface("data/image/explosion.png");
}

void Explosion::draw()
{

}

void Explosion::update()
{

}
