#pragma once

#include <vector>
#include <algorithm>
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

    void draw();

    void add(GameObject*);

    /* sady miCreer objet no miAjouter anlay izy anaty groupe */
    /* ex : Enemy* enemy = group.create<Slime>(player, x, y); */
    template<typename objectType, typename... argType>
    objectType* create(argType&&... args)
    {
        if (std::is_base_of<GameObject, objectType>::value == false)
            return nullptr;
        objectType *obj = new objectType(std::forward<argType>(args)...);
        add(obj);
        return obj;
    }

    void remove(GameObject*);
    /* amzay tsika afak manao hoe :
		enemies.remove({ truc, bidule, chose });
     */
    void remove(const std::vector<GameObject*>&);

    bool has(GameObject*);

friend class GameObject;
};
