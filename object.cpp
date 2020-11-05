#include "object.h"
#include "group.h"

void GameObject::update()
{}

void GameObject::draw(SDL_Surface* screen)
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
