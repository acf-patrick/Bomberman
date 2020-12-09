#include "group.h"
#include "object.h"
#include "renderer.h"
#include <algorithm>

std::vector<GameObject*> Group::collector;

Group::~Group()
{
	// already cleaned
	if (!collector.empty())
	{
		for (auto &obj : collector)
			delete obj;
		collector.clear();
	}

    for (int i = 0; i<(int)objects.size(); ++i)
    {
    	delete objects[i];
    	objects[i] = nullptr;
    }
}

void Group::update()
{
    for (auto &object : objects)
		object->update();
}

void Group::draw()
{
	SDL_Rect camera(Renderer::camera->getViewport());
	for (auto &object : objects)
		// zay hita eo am écran ian no dessinena
		// if (object->collide(camera))
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

GameObject* Group::firstObjectCollidingWith(GameObject& object)
{
    for (auto& obj : objects)
		if (mutual_collision(*obj, object))
            return obj;
	return nullptr;
}
