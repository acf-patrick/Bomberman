#ifndef TIMER_H
#define TIMER_H

#include <SDL/SDL.h>

class Timer
{
	private:
	    float start_time, stop_time;
	    bool is_running, is_stopped;
	public:
	    Timer();
	    void start();
	    void stop();
	    float get_time();
	    bool get_state();
};


#endif
