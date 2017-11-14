#ifndef __J1ENTITY_H__
#define __J1ENTITY_H__

#include "j1App.h"
#include "p2Point.h"
#include "j1Textures.h"
#include "Animation.h"
#include "p2List.h"
#include "j1Physics.h"


struct entity_property
{
	float value;
	p2SString name;
	int type;
};

enum ENTITY_TYPE
{
	BACKGROUND,
	BAT,
	PLAYER,
	ENEMY
};

class Entity
{
public:

	p2SString	name;

	iPoint position;
	SDL_Texture* texture;
	bool interactive;
	ENTITY_TYPE type;
	Animation* current_animation = nullptr;
	object* obj = nullptr;

public:
	
	Entity() {};
	~Entity() {
	//	LOG("I've been deleted, ouch!");
	};
	
	void SetPos(iPoint pos) 
	{ 
		position = pos; 
	};

	void LoadTex(const char* path) 
	{
		texture = App->tex->Load(path);
	};

	virtual void Draw() {};
	ENTITY_TYPE Get_type()
	{
		return type;
	}
	virtual bool PreUpdate(float dt) { return true; };
	virtual bool Update(float dt) { return true; };
	virtual bool PostUpdate(float dt) { return true; };

	virtual void Awake() {};
	virtual void Start() {};

	virtual void OnCollision(Collider* c1, Collider* c2) {};
	
	virtual void CleanUp() { App->tex->UnLoad(texture); obj = nullptr; };

	virtual bool Save(pugi::xml_node& node)const { return true; }; 
	virtual bool Load(pugi::xml_node& node) { return true; };
};
#endif // !__J1ENTITY_H__
