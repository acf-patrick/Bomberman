#include "group.h"

Group::~Group()
{
	int i(0);
    for (auto &object : objects)
    {
    	delete object;
    	objects[i] = nullptr;
    	++i;
    }
}

void Group::update()
{
    for (auto &object : objects)
		object->update();
}

void Group::draw(SDL_Surface* screen)
{
	for (auto &object : objects)
		object->draw(screen);
}
