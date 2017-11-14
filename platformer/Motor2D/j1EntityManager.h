#ifndef __J1ENTITIES_H__
#define __J1ENTITIES_H__

#include "j1Module.h"
#include "p2Point.h"
#include "j1Collision.h"
#include "Entity.h"
#include "p2List.h"
#include "p2DynArray.h"



class j1EntityManager : public j1Module
{
public:
	j1EntityManager();
	~j1EntityManager() {
		p2List_item<entity_property*>* item_1 = properties.start;
		while (item_1 != nullptr)
		{
			RELEASE(item_1->data);
			item_1 = item_1->next;
		}
		properties.clear();
	};


	bool PreUpdate(float dt);
	bool Update(float dt);
	bool PostUpdate(float dt);

	bool Awake(pugi::xml_node& config);

	Entity* AddEntity(int x, int y,ENTITY_TYPE type);

	void OnCollision(Collider* c1, Collider* c2);

	//void Draw();

	bool CleanUp();

	bool Save(pugi::xml_node& node)const;
	bool Load(pugi::xml_node& node);

	p2List<Entity*> entities;
	p2List<entity_property*> properties;
	
};
#endif // !__J1ENTITIES_H__
