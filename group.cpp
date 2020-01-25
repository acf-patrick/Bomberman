#include "group.h"
#include <algorithm>

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

void Group::add(GameObject *object)
{
	/* ne rien faire, si null */
    if (!object)
		return;

	/* Si l'objet n'y est pas encore */
	if (!has(object))
		objects.push_back(object);

	object->groups.push_back(this);
}

bool Group::has(GameObject *object)
{
	return (std::find(std::begin(objects), std::end(objects), object) != objects.end());
}

void Group::remove(GameObject *object)
{
	/*
        Iter std::remove(Iter begin, Iter end, const T& value);
        alàny zay item mtov (mapiasa operator==) amin'i "value".
        ex :
			vector<int> t = { 1, 2, 3, 1, 4, 5, 1, 6, 0, 1 };
			auto it = std::remove(std::begin(t), std::end(t), 1);
		maazo 't' lasa hoe : { 2, 3, 4, 5, 6, 0, 1, 1, 1, 1 }
        it : miPoint eo amn'ilay élément tkn ho faran'ilay conteneur,
        zany hoe 7ième élément iz amn'io éxemple io.
        Mapiasa méthode "erase" anatin'ny conteneur ftsn aveo :
			t.erase(it, std::end(t));
		miala daolo lay 1, 1, 1, 1 any amin'ny farany. Maazo hoe:
			t = { 2, 3, 4, 5, 6, 0 }
		ts haiko na efa kobonla fa apetrako eto iany ... nanao
		an'ity ah mants vao azko tsara xD
	*/
	/* ne rien faire, si null */
    if (!object)
		return;

	/* on l'enlève juste de la liste des objets */
    objects.erase(std::remove(std::begin(objects), std::end(objects), object), std::end(objects));

    std::vector<Group*> &g(object->groups);
    g.erase(std::remove(std::begin(g), std::end(g), this), std::end(g));
}
