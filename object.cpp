#include "object.h"
#include "group.h"

void GameObject::update()
{}

void GameObject::draw()
{}

void GameObject::move(float x, float y)
{
	Vector<float> offset(x, y);
	position += offset;
}

Vector<float> GameObject::getPosition() const { return position; }

void GameObject::setPosition(float x, float y) { position.setCartesian(x, y); }

void GameObject::setSize(int w, int h) { size.setCartesian(w, h); }

Vector<int> GameObject::getSize() const { return size; }

SDL_Rect GameObject::getBoundingBox() const
{
	return SDL_Rect { (Sint16)position.x, (Sint16)position.y,
					(Uint16)size.x, (Uint16)size.y};
}

bool GameObject::isAlive() const { return !groups.empty(); }

std::vector<Group*> GameObject::getOwner() const { return groups; }

void GameObject::kill()
{
    for (auto &group : groups)
		group->remove(this);
	groups.clear();
}

bool GameObject::collide(const GameObject& obj) const
{
	const Vector<float> &pos = obj.position;
	const Vector<int> &s = obj.size;
	return (
            position.x <= pos.x+s.x and
            position.y <= pos.y+s.y and
            position.x+size.x >= pos.x and
            position.y+size.y >= pos.y
			);
}

bool GameObject::collide(const SDL_Rect& rect) const
{
	GameObject obj;
	obj.setPosition(rect.x, rect.y);
	obj.setSize(rect.w, rect.h);
	return collide(obj);
}

/* mety samy manana ny méthode "collide" ny o1 sy o2
dia ts maints checkena daoly iz roa ... virtual mants iz ao
 */
bool mutual_collision(const GameObject& o1, const GameObject& o2)
{ return o1.collide(o2) and o2.collide(o2); }

bool GameObject::collide(Group *group, bool _kill) const
{
	bool ret(false);
	std::vector<GameObject*> to_remove;
    for (auto &object : group->objects)
		if (mutual_collision(*object, *this))
		{
			ret = true;
			if (_kill)
				to_remove.push_back(object);
		}

	/* segfault manadala rah natao tanatin'lay boucle ...
	sad miIterer anlay container "objects" mants no manàla
	item */
	for (auto &object : to_remove)
		group->remove(object);
	return ret;
}

std::vector<GameObject*> GameObject::collide(const Group& group) const
{
    std::vector<GameObject*> ret;
    for (auto &obj : group.objects)
		if (mutual_collision(*obj, *this))
			ret.push_back(obj);
    return ret;
}
