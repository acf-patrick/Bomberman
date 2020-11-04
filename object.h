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

	virtual void update();
	virtual void draw(SDL_Surface*);

	void move(float, float);

	Vector<float> getPosition();
	void setPosition(float, float);

	std::vector<Group*> getOwner();

	bool isAlive();

	void kill();

friend class Group;
};
