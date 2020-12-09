#include "defs.h"
#include "renderer.h"
#include "explosion.h"
#include "assetsmanager.h"

Group Explosion::group;
int** Explosion::map = nullptr;

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
		surface[i] = SDL_CreateRGBSurface(SDL_SWSURFACE, size.x, size.y, 32, 0, 0, 0, 0);
		if (!surface[i])
		{
			std::cerr << "erreur lors de la création de l'éxplosion" << std::endl;
			continue;
		}
		SDL_FillRect(surface[i], NULL, 0xff00ff);

		// center
		SDL_Rect src = { 0, Sint16(i*PX), PX, PX }, center = { Sint16((size.x-PX)*0.5), Sint16((size.y-PX)*0.5) };
		SDL_Rect dest(center);
		SDL_BlitSurface(spritesheet, &src, surface[i], &dest);

		int k;

		dest.x = center.x;
		dest.y = center.y;
		src.x = Sint16((i+1)*PX);
		src.y = PX;
		for (k=1; k<=range+1; ++k)
		{
            dest.y -= PX;
            if (y-k <= 0)
				break;
            else if (map[y-k][x] != GROUND)
				break;
			if (k == range+1)
			{
				src.y = 0;
				dest.y = 0;
			}
            SDL_BlitSurface(spritesheet, &src, surface[i], &dest);
		}

		dest.x = center.x;
		dest.y = center.y;
		src.x = Sint16((i+1)*PX);
		src.y = PX;
		for (k=1; k<=range+1; ++k)
		{
            dest.y += PX;
            if (y+k >= MAP_H)
				break;
            else if (map[y+k][x] != GROUND)
				break;
			if (k == range+1)
			{
				src.y = 2*PX;
				dest.y = Sint16(size.y - PX);
			}
            SDL_BlitSurface(spritesheet, &src, surface[i], &dest);
		}

		dest.x = center.x;
		dest.y = center.y;
		src.x = PX;
		src.y = Sint16((i+3)*PX);
		for (k=1; k<=range+1; ++k)
		{
            dest.x -= PX;
            if (x-k < 0)
				break;
			else if (map[y][x-k] != GROUND)
                break;
			if (k == range+1)
			{
				src.x = 0;
				dest.x = 0;
			}
            SDL_BlitSurface(spritesheet, &src, surface[i], &dest);
		}

		dest.x = center.x;
		dest.y = center.y;
		src.x = PX;
		src.y = Sint16((i+3)*PX);
		for (k=1; k<=range+1; ++k)
		{
            dest.x += PX;
            if (x+k >= MAP_W)
				break;
			else if (map[y][x+k] != GROUND)
                break;
			if (k == range+1)
			{
				dest.x = Sint16(size.x-PX);
				src.x = 2*PX;
			}
            SDL_BlitSurface(spritesheet, &src, surface[i], &dest);
		}

		SDL_SetColorKey(surface[i], SDL_SRCCOLORKEY, 0xff00ff);
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
