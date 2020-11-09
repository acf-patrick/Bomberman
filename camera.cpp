#include "camera.h"
#include "object.h"

Camera::Camera(GameObject *obj) : focus(obj)
{}

void Camera::init(const SDL_Rect& rect)
{
    position.x = rect.x;
    position.y = rect.y;
	size.x = rect.w;
	size.y = rect.h;
}

void Camera::update()
{
    Vector<float> objPos(focus->getPosition());
    Vector<int> objSize(focus->getSize());
    position.setCartesian((objPos.x+objSize.x*0.5)-0.5*size.x, (objPos.y+objSize.y*0.5)-0.5*size.y);

    if (position.x < 0)
		position.x = 0;
    if (position.y < 0)
		position.y = 0;
	if (position.x > limit.x - size.x)
        position.x = limit.x - size.x;
	if (position.y > limit.y - size.y)
        position.y = limit.y - size.y;
}

void Camera::setLimit(int x, int y)
{ limit.setCartesian(x, y); }

Vector<int> Camera::convert(int x, int y)
{ return Vector<int>(x-position.x, y-position.y); }

SDL_Rect Camera::getViewport()
{ return SDL_Rect { Sint16(position.x), Sint16(position.y), Uint16(size.x), Uint16(size.y) }; }
