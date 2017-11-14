#include "j1EntityManager.h"
#include "j1Collision.h"
#include "j1App.h"
#include "p2Log.h"
#include "EntityPlayer.h"
#include "Brofiler\Brofiler.h"

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
			entity_property* iterator_property = new entity_property;
			iterator_property->name.create(propertie.attribute("name").as_string("failed_loading"));
			iterator_property->value = propertie.attribute("value").as_float(-1);
			iterator_property->type = i;
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
	BROFILER_CATEGORY("AddEntity_EntityManager", Profiler::Color::DarkOliveGreen);

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
	
	ret->Awake();
	ret->Start();

	entities.add(ret);
	return ret;

}

bool j1EntityManager::CleanUp()
{
	BROFILER_CATEGORY("CleanUp_EntityManager", Profiler::Color::DarkOliveGreen);

	LOG("Freeing all objects");
	p2List_item<Entity*>* item = entities.start;
	while(item != NULL)
	{
		App->tex->UnLoad(item->data->texture);
		item->data->CleanUp();
		RELEASE(item->data);
		item = item->next;
	}
	entities.clear();

	return true;
}

bool j1EntityManager::PreUpdate(float dt)
{
	BROFILER_CATEGORY("PreUpdate_EntityManager", Profiler::Color::DarkOliveGreen);

	p2List_item<Entity*>* item = entities.start;
	while (item != nullptr)
	{
		item->data->PreUpdate(dt);
		item = item->next;
	}
	return true;
}

bool j1EntityManager::Update(float dt)
{
	BROFILER_CATEGORY("Update_EntityManager", Profiler::Color::DarkOliveGreen);

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

bool j1EntityManager::PostUpdate(float dt)
{
	BROFILER_CATEGORY("PostUpdate_EntityManager", Profiler::Color::DarkOliveGreen);

	p2List_item<Entity*>* item = entities.start;
	while (item != nullptr)
	{
		item->data->PostUpdate(dt);
		item = item->next;
	}
	return true;
}

void j1EntityManager::OnCollision(Collider* c1, Collider*c2)
{
	BROFILER_CATEGORY("OnCollision_EntityManager", Profiler::Color::DarkOliveGreen);

	p2List_item<Entity*>* item = entities.start;
	while (item != NULL)
	{
		if (item->data->interactive)
		{
			// this is to talk to the item as an interactive item that has the obj property;
			if (item->data->obj != nullptr &&
				c1->rect.x == item->data->obj->col->rect.x &&
				c1->rect.y == item->data->obj->col->rect.y &&
				c1->type == item->data->obj->col->type)
			{
				item->data->OnCollision(c1, c2);
			}
			
		}
		item = item->next;
	}
};

bool j1EntityManager::Save(pugi::xml_node& node) const
{
	BROFILER_CATEGORY("Save_EntityManager", Profiler::Color::DarkOliveGreen);

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
	BROFILER_CATEGORY("Load_EntityManager", Profiler::Color::DarkOliveGreen);

	p2List_item<Entity*>* item = entities.start;
	while (item != nullptr)
	{
		item->data->Load(node);
		item = item->next;
	}
	return true;
}
