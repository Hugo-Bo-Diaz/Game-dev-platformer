#include "j1EntityManager.h"
#include "j1Collision.h"
#include "j1App.h"
#include "p2Log.h"

j1EntityManager::j1EntityManager()
{
	//here we initialise all object to nullptr

}

bool j1EntityManager::Awake(pugi::xml_node* config)
{
	/*objects = new object[MAX_OBJECTS];

	memset(objects, 0, sizeof(object)*(MAX_OBJECTS));*/

	return true;
}

Entity* j1EntityManager::AddEntity(int _x, int _y, ENTITY_TYPE type)
{
	Entity* ret = nullptr;

	//assign all the entity properties
	ret->position.x = _x;
	ret->position.y = _y;
	ret->type = type;

	entities.add(ret);
	return ret;

}

bool j1EntityManager::CleanUp()
{
	LOG("Freeing all objects");
	p2List_item<Entity*>* item = entities.start;
	while(item != nullptr)
	{
		delete item;
		item = item->next;
	}

	return true;
}

bool j1EntityManager::PreUpdate()
{
	p2List_item<Entity*>* item = entities.start;
	while (item != nullptr)
	{
		item->data->PreUpdate();
		item = item->next;
	}
	return true;
}

bool j1EntityManager::Update()
{
	p2List_item<Entity*>* item = entities.start;
	while (item != nullptr)
	{
		item->data->PostUpdate();
		item = item->next;
	}
	return true;	return true;
}

bool j1EntityManager::PostUpdate()
{
	p2List_item<Entity*>* item = entities.start;
	while (item != nullptr)
	{
		item->data->PostUpdate();
		item = item->next;
	}
	return true;	return true;
}

void j1EntityManager::OnCollision(Collider* c1, Collider*c2)
{
	if (c1->type == COLLIDER_FUTURE && c2->type == COLLIDER_WALL)
	{

	}
};

void j1EntityManager::Draw()
{
	p2List_item<Entity*>* item = entities.start;
	while (item != nullptr)
	{
		item->data->Draw();
		item = item->next;
	}
}

bool j1EntityManager::Save(pugi::xml_node& node) const
{
	p2List_item<Entity*>* item = entities.start;
	while (item != nullptr)
	{
		item->data->Save(node);
		item = item->next;
	}

}

bool j1EntityManager::Load(pugi::xml_node& node)
{
	p2List_item<Entity*>* item = entities.start;
	while (item != nullptr)
	{
		item->data->Load(node);
		item = item->next;
	}

}