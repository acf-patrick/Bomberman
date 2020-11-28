#include "group.h"
#include "object.h"
#include <algorithm>
#include "renderer.h"

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

void Group::draw()
{
	for (auto &object : objects)
		// zay hita eo am écran ian no dessinena
		if (object->collide(Renderer::camera->getViewport()))
			object->draw();
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
	/* ne rien faire, si null */
    if (!object)
		return;

	/* on l'enlève juste de la liste des objets */
    objects.erase(std::remove(std::begin(objects), std::end(objects), object), std::end(objects));

    std::vector<Group*> &g(object->groups);
    g.erase(std::remove(std::begin(g), std::end(g), this), std::end(g));
}

