#pragma once

#include "object.h"
#include "vector.h"
#include "timer.h"
#include "renderer.h"


class GameObject;

class Bomb: public GameObject
{
    private:
        SDL_Surface *sprite;
        SDL_Rect blit_pos;
        Timer timer;
        bool is_set;
    public:
        Bomb(float , float);
        ~Bomb() {};
       void update() override final;
	   void draw() override final;

};
