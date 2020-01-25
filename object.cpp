#include "object.h"

void GameObject::update()
{}

void GameObject::draw(SDL_Surface* screen)
{}

void GameObject::move(float x, float y)
{
	Vector<float> offset(x, y);
	position += offset;
}

Vector<float> GameObject::getPosition() { return position; }

void GameObject::setPosition(float x, float y) { position.setCartesian(x, y); }

