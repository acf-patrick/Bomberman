#pragma once

#include "vector.h"

class GameObject;

class Camera
{
private:
	/* lay objet arahana */
	GameObject *focus;
	Vector<int> position;
	Vector<int> limit;
	Vector<int> size;

public:
	Camera(GameObject*);

	void init(const SDL_Rect&);
    /* definissena hoe atraiza ian 'lay camera no afk mandende */
	void setLimit(const Vector<int>&);
	void update();
};
