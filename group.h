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

    /* met-à-jour tous les objets de ce groupe */
    void update();
    /* déssine tous les objets de ce groupe */
    void draw(SDL_Surface*);

    void add(GameObject*);

    void remove(GameObject*);

    bool has(GameObject*);
};
