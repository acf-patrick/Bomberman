#pragma once

#include <SDL/SDL.h>

class Timer
{
public:
	enum State { RUNNING, STOPPED };

	Timer();
	void start();
	void stop();
	int get_elapsed_time();
	int get_stop_time();

	bool get_state();

private:
	int start_time, stop_time;
	State state;
};
