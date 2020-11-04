#pragma once

#include <vector>
#include "object.h"

class Group
{
private:
    std::vector<GameObject*> objects;

public:
    Group() {}
    virtual ~Group();

    void update();

    void draw(SDL_Surface*);

    void add(GameObject*);

    void remove(GameObject*);

    bool has(GameObject*);
};
