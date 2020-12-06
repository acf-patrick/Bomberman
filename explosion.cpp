#include "defs.h"
#include "renderer.h"
#include "explosion.h"
#include "assetsmanager.h"

// for transparency
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    #define RMASK 0xff000000
    #define GMASK 0x00ff0000
    #define BMASK 0x0000ff00
    #define AMASK 0x000000ff
#else
    #define AMASK 0xff000000
    #define BMASK 0x00ff0000
    #define GMASK 0x0000ff00
    #define RMASK 0x000000ff
#endif

Group Explosion::group;

Explosion::Explosion(int x, int y, int portee):
    dt (100)
{
	group.add(this);

	range = portee;
	state = 0;
	sens = 1;

	position.setCartesian(x*PX, y*PX);
	size.setCartesian((2*(range+1)+1)*PX, (2*(range+1)+1)*PX);

	spritesheet = AssetManager::instance->get_surface("explosion");
	if (!spritesheet)
		spritesheet = AssetManager::instance->load_surface("./data/images/explosion.png");

	for (int i=0; i<3; ++i)
	{
		surface[i] = SDL_CreateRGBSurface(SDL_HWSURFACE, size.x, size.y, 32, RMASK, GMASK, BMASK, AMASK);
		if (!surface[i])
		{
			std::cerr << "erreur lors de la création de l'éxplosion" << std::endl;
			continue;
		}

		// center
		SDL_Rect src = { 0, Sint16(i*PX), PX, PX }, dest = { Sint16((size.x-PX)*0.5), Sint16((size.y-PX)*0.5) };
		SDL_BlitSurface(spritesheet, &src, surface[i], &dest);

		// top
		src.x = Sint16((i+1)*PX);
		src.y = 0;
		dest.y = 0;
		SDL_BlitSurface(spritesheet, &src, surface[i], &dest);

		// vertical
		src.y += PX;
		for (int k=0; k<=2*range; ++k)
		{
			dest.y += PX;
			// avoid center
			if (k != range)
				SDL_BlitSurface(spritesheet, &src, surface[i], &dest);
		}

		// bottom
		src.y += PX;
		dest.y = Sint16(size.y - PX);
		SDL_BlitSurface(spritesheet, &src, surface[i], &dest);

		// left
		src.x = 0;
		src.y = Sint16((i+3)*PX);
		dest.x = 0;
		dest.y = Sint16((size.y-PX)*0.5);
		SDL_BlitSurface(spritesheet, &src, surface[i], &dest);

		// horizontal
		src.x += PX;
		for (int k=0; k<=2*range; ++k)
		{
			dest.x += PX;
			// avoid center
			if (k != range)
				SDL_BlitSurface(spritesheet, &src, surface[i], &dest);
		}

		// right
		src.x += PX;
		dest.x = Sint16(size.x-PX);
		SDL_BlitSurface(spritesheet, &src, surface[i], &dest);
		SDL_SetColorKey(surface[i], SDL_SRCCOLORKEY, 0xff00ffff);
	}

	timer.start();
}

void Explosion::draw()
{
    Vector<int> p(Renderer::camera->convert(position.x - (size.x-PX)*0.5, position.y - (size.y-PX)*0.5));
    SDL_Rect pos = { Sint16(p.x), Sint16(p.y) };
    SDL_BlitSurface(surface[state], NULL, Renderer::screen, &pos);
}

void Explosion::update()
{
	if (state == 0 and sens < 0)
		kill();

	if (timer.get_elapsed_time() >= dt)
	{
        if (state == 2)
            sens *= -1;
        state += sens;
		timer.start();
	}
}

bool Explosion::collide(const GameObject& obj) const
{
	return false;
}
