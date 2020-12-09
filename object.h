#pragma once

#include <SDL/SDL.h>
#include <vector>
#include "vector.h"

class Group;

class GameObject
{
protected:
	Vector<float> position;
	Vector<int> size;

	std::vector<Group*> groups;

public:
	GameObject() {}
	virtual ~GameObject() {}

	virtual void update();
	virtual void draw();

	virtual void move(float, float);

	Vector<float> getPosition() const;
	void setPosition(float, float);

	Vector<int> getSize() const;
	void setSize(int, int);

	std::vector<Group*> getOwner() const;

	bool isAlive() const;

	void kill();

	/* ........................................... */
	virtual bool collide(GameObject&);
	virtual bool collide(SDL_Rect&);

	bool collide(Group*, bool _kill = false);

	std::vector<GameObject*> collide(Group&);
	/* ........................................... */


	SDL_Rect getBoundingBox() const;

friend class Group;
};

bool mutual_collision(GameObject&, GameObject&);
