#include "bomb.h"
#include "defs.h"
#include "assetsmanager.h"
#include <SDL/SDL.h>

int Bomb::number = 0;

Bomb::Bomb(int x, int y)
{
    // x = (x/PX)*PX;
    // y = (y/PX)*PX;
    number++;

    position.setCartesian(x , y);
    size.setCartesian(24, 24);
    sprite = AssetManager::instance->get_surface("bomb");
    if (!sprite)
        sprite = AssetManager::instance->load_surface("./data/images/bomb.png");
    cur_frame = 0;
}

Bomb::~Bomb()
{
    number--;
}

void Bomb::update()
{
    if (timer.get_elapsed_time() > 100)
    {
        cur_frame = (cur_frame+1)%3;
        timer.start();
    }
}

void Bomb::draw()
{
    Vector<int> pos(Renderer::camera->convert(position.x, position.y));
    SDL_Rect tmp = { Sint16(pos.x), Sint16(pos.y) },
    blit_pos = {
        Sint16(cur_frame*size.x), 0,
        Uint16(size.x), Uint16(size.y)
    };
    SDL_BlitSurface(sprite, &blit_pos,Renderer::screen, &tmp);
}
