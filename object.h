#pragma once

#include <SDL/SDL.h>
#include <vector>
#include "vector.h"

class Group;

class GameObject
{
private:
	Vector<float> position;
	std::vector<Group*> groups;

public:
	GameObject() {}
	virtual ~GameObject() {}

	/* servira à mettre à jour l'objet à chaque tour de boucle */
	virtual void update();
	virtual void draw(SDL_Surface*);

	void move(float, float);

	Vector<float> getPosition();
	void setPosition(float, float);
};
