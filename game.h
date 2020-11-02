#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "timer.h"
#include "vector.h"

class Game
{
    private:
        SDL_Surface *screen, *start_s;
        bool running, at_start_s;
        Timer start_t;
    public:
        Game();
        ~Game();
        void run();
        void start();
};

#endif // GAME_H
