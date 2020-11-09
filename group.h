#pragma once

#include <vector>
#include <SDL/SDL.h>

class GameObject;

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
    /* amzay tsika afak manao hoe :
		enemies.remove({ truc, bidule, chose });
     */
    void remove(const std::vector<GameObject*>&);

    bool has(GameObject*);

friend class GameObject;
};
