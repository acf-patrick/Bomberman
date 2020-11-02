#pragma once

#include <SDL/SDL.h>

/* Novaiko variable ray ilay is_running sy is_stopped
  dia ao amn'io enumeration io ny valeur azony raisina
*/

class Timer
{
public:
	enum State { RUNNING, STOPPED };

	Timer();
	void start();
	void stop();
	int get_elapsed_time();
	int get_stop_time();

	/**
	* @return true if running, else, false
	*/
	bool get_state();

private:
	int start_time, stop_time;
	State state;
};
