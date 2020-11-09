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
	virtual void draw();

	void move(int, int);

	Vector<float> getPosition() const;
	void setPosition(float, float);

	Vector<int> getSize() const;
	void setSize(int, int);

	std::vector<Group*> getOwner() const;

	bool isAlive() const;

	void kill();

	/* ........................................... */
	virtual bool collide(const GameObject&) const;
	virtual bool collide(const SDL_Rect&) const;

	/*
	cas anty ohatra hoe nisy bomb nipoaka, dia nisy enemy
	maromaro voa; rah destroy == true dia alàna tao amn'io
	groupe io lay enemies.
	miRetourne iz aveo hoe nis voa na tsia
	*/
	bool collide(Group*, bool _kill = false) const;

    /*
	otrotrn'io ambony io ihany fa au lieu hoe tng dia potehana
	dia maazo liste anreo miEntrer en collision amty objet ity
	dia hit eo zay atao...oatra hoe alaina alou ny position any,
	inh oatra ny typenlay enemy...otrotrzany
    */
	std::vector<GameObject*> collide(const Group&) const;
	/* ........................................... */

    /* mReturn anlay rect miEnglober anlay objet
	sod mis ilàna azy any aoriana any
    */
	SDL_Rect getBoundingBox() const;

friend class Group;
};
