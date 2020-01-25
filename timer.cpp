#include "timer.h"

Timer::Timer()
{
	start_time = 0;
	stop_time = 0;
	state = STOPPED;
}

void Timer::start()
{
	start_time = SDL_GetTicks();
	state = RUNNING;
}

void Timer::stop()
{
	state = STOPPED;
	start_time = 0;
	stop_time = SDL_GetTicks();
}

int Timer::get_elapsed_time()
{
	return SDL_GetTicks() - start_time;
}

int Timer::get_stop_time()
{
	return stop_time;
}

bool Timer::get_state()
{
	return state == RUNNING;
}
