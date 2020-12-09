#pragma once

#include <vector>
#include <algorithm>
#include <SDL/SDL.h>

class GameObject;

class Group
{
private:
    std::vector<GameObject*> objects;

    // mis anren objet antsoina ftsn ny méthode kill
    // ts détruit zan lay objet fa mbola anaty mémoir ao
    // stockena ato amty daoly dia destroyena fts aveo
    static std::vector<GameObject*> collector;

public:

    static void clean();

    Group() {}
    virtual ~Group();

    void update();

    void draw();

    void add(GameObject*);

    /* sady miCreer objet, no miAjouter anlay izy anaty groupe */
    /* ex : Enemy* enemy = group.create<Slime>(player, x, y); */
    template<typename objectType, typename... argType>
    objectType* create(argType&&... args)
    {
        // checkena sod ts GameObject
        if (std::is_base_of<GameObject, objectType>::value == false)
            return nullptr;
        objectType *obj = new objectType(std::forward<argType>(args)...);
        add(obj);
        return obj;
    }

    void remove(GameObject*);
    void remove(const std::vector<GameObject*>&);

    bool has(GameObject*);

    GameObject* firstObjectCollidingWith(GameObject&);

    using iterator = std::vector<GameObject*>::iterator;

    iterator begin()
    { return objects.begin(); }
    iterator end()
    { return objects.end(); }

friend class GameObject;
};
