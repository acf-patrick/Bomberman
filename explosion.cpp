#include "renderer.h"
#include "explosion.h"
#include "assetsmanager.h"

Group Explosion::group;

Explosion::Explosion(int x, int y, int portee)
{
	group.add(this);

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
