#ifndef __J1ENTITIES_H__
#define __J1ENTITIES_H__

#include "j1Module.h"
#include "p2Point.h"
#include "j1Collision.h"
#include "Entity.h"
#include "p2List.h"

class j1EntityManager : public j1Module
{
public:
	j1EntityManager();
	~j1EntityManager() {};

	bool PreUpdate();
	bool Update();
	bool PostUpdate();

	bool Awake(pugi::xml_node* config);

	Entity* AddEntity(int x, int y,ENTITY_TYPE type);

	void OnCollision(Collider* c1, Collider* c2);

	void Draw();

	bool CleanUp();

	p2List<Entity*> entities;

	bool Save(pugi::xml_node& node)const;
	bool Load(pugi::xml_node& node);
};
#endif // !__J1ENTITIES_H__
