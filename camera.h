#pragma once

#include <SDL/SDL.h>
#include "vector.h"

class GameObject;

class Camera
{
private:
	/* lay objet arahana */
	GameObject *focus;
	/* position anlay fenêtre par rapport amlay repere global ty n'tena marn */
	/* sad coordonnées anlay camera ian zan */
	Vector<int> position;
	Vector<int> size, limit;

public:
	Camera(GameObject*);

	void init(const SDL_Rect&);
    /* definissena hoe atraiza ian 'lay camera no afk mandende */
	void setLimit(int, int);
	void update();

    /* ty lay maka coordonnées global dia avadiny coords local */
    /* lay coordonnées azo aveo no apesaina anaovana blit */
    /* anaty champ anlay camera foana iz amza, dia ref ahisaka lay camera*/
    /* dia otrn hoe miscroll */
    Vector<int> convert(int, int);

    SDL_Rect getViewport();
};
