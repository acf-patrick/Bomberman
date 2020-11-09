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
	if (position.x > limit.x)
        position.x = limit.x;
	if (position.y > limit.y)
        position.y = limit.y;
}

void Camera::setLimit(const Vector<int>& l)
{ limit.setCartesian(l.x, l.y); }
