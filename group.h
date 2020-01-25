#pragma once

#include <vector>
#include "object.h"

class Group
{
private:
    std::vector<GameObject*> objects;

public:
    Group() {}
    ~Group();

    void update();
    void draw(SDL_Surface*);

};
