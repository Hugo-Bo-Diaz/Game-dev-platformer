#include "j1EntityManager.h"
#include "j1Collision.h"
#include "j1App.h"
#include "p2Log.h"
#include "EntityPlayer.h"

j1EntityManager::j1EntityManager()
{
	name.create("Entities");
	//here we initialise all object to nullptr

}

bool j1EntityManager::Awake(pugi::xml_node& config)
{
	pugi::xml_node node_entities = config;

	pugi::xml_node entity;
	int i = 0;
	for (entity = node_entities.first_child(); entity; entity = entity.next_sibling())// there are more entities with properties
	{
		pugi::xml_node propertie = entity.first_child();
		i = entity.attribute("type").as_int(-1);
		for (propertie = entity.first_child(); propertie; propertie = propertie.next_sibling())//there are still properties left
		{
			entity_property iterator_property;
			iterator_property.name.create(propertie.attribute("name").as_string("failed_loading"));
			iterator_property.value = propertie.attribute("value").as_float(-1);
			iterator_property.type = i;
			properties.add(iterator_property);
		}
	}

	/*p2List_item<Entity*>* item;
	item = entities.start;
	while (item != NULL)
	{
		item->data->Awake(config.child(item->data->name.GetString()));
		item = item->next;
	}*/

	return true;
}

Entity* j1EntityManager::AddEntity(int _x, int _y, ENTITY_TYPE type)
{
	Entity* ret;
	int list_of_properties = -1;
	switch (type)
	{
	case ENTITY_TYPE::PLAYER:
	{
		ret = new EntityPlayer;
		list_of_properties = 0;
	}
	default:
		ret = new EntityPlayer;
	}

	//assign all the entity properties
	ret->SetPos(iPoint(_x,_y));
	ret->type = type;
	
	//char number = (char)entities.find(ret);// the entity name will be its number on the list by default
	//ret->name.create(&number);
	
	ret->Awake();
	ret->Start();
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

bool j1EntityManager::Update(float dt)
{
	p2List_item<Entity*>* item = entities.start;
	while (item != nullptr)
	{
		item->data->Update(dt);
		item = item->next;
	}

	p2List_item<Entity*>* item_1 = entities.start;
	while (item_1 != nullptr)
	{
		item_1->data->Draw();
		item_1 = item_1->next;
	}
	return true;
}

bool j1EntityManager::PostUpdate()
{
	p2List_item<Entity*>* item = entities.start;
	while (item != nullptr)
	{
		item->data->PostUpdate();
		item = item->next;
	}
	return true;
}

void j1EntityManager::OnCollision(Collider* c1, Collider*c2)
{
	if (c1->type == COLLIDER_FUTURE && c2->type == COLLIDER_WALL)
	{

	}
};

bool j1EntityManager::Save(pugi::xml_node& node) const
{
	p2List_item<Entity*>* item = entities.start;
	while (item != nullptr)
	{
		item->data->Save(node);
		item = item->next;
	}
	return true;
}

bool j1EntityManager::Load(pugi::xml_node& node)
{
	p2List_item<Entity*>* item = entities.start;
	while (item != nullptr)
	{
		item->data->Load(node);
		item = item->next;
	}
	return true;
}