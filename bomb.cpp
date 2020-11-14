#include "bomb.h"

Bomb::Bomb(float x, float y)
{
    position.setCartesian(x , y);
    size.setCartesian(30, 30);
    sprite = IMG_Load("./data/images/bomb.png");
    blit_pos = {0, 0, 30, 30};
    is_set = false;
}

void Bomb::update()
{
    if (is_set)
    {
        if (timer.get_state() == Timer::STOPPED)
            timer.start();
        if (timer.get_elapsed_time() > 100)
        {
            if (blit_pos.x < 60)
                blit_pos.x += 30;
            else
                blit_pos.x = 0;
            if (timer.get_elapsed_time() > 3000)
            {
                 timer.stop();
                 is_set = false;
            }
        }
    }
}

void Bomb::draw()
{
    Vector<int> pos(Renderer::camera->convert(position.x, position.y));
    SDL_Rect tmp =
    {
        Sint16(pos.x), Sint16(pos.y),
        Uint16(size.x), Uint16(size.y)
    };
    if (is_set)
    SDL_BlitSurface(sprite, &blit_pos,Renderer::screen, &tmp);
}
