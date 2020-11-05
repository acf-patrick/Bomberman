#pragma once

#include <SDL/SDL.h>
#include <vector>
#include "vector.h"

class Group;

class GameObject
{
private:
	Vector<float> position;

    /* efa natao objet vector 'lay position, satria nilaina natao float,
       dia aleo atao vector lay size fa ts SDL_Rect...lasa redondant lay position */
	Vector<int> size;

	std::vector<Group*> groups;

public:
	GameObject() {}
	virtual ~GameObject() {}

	virtual void update();
	virtual void draw(SDL_Surface*);

	void move(float, float);

	Vector<float> getPosition() const;
	void setPosition(float, float);

	Vector<int> getSize() const;
	void setSize(int, int);

	std::vector<Group*> getOwner() const;

	bool isAlive() const;

	void kill();

	/* hidetectena collision */
	virtual bool collide(const GameObject&) const;
	virtual bool collide(const SDL_Rect&) const;

    /* mReturn anlay rect miEnglober anlay objet
	sod mis ilàna azy any aoriana any
    */
	SDL_Rect getBoundingBox() const;

friend class Group;
};
