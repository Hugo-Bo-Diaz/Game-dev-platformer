#ifndef __J1PHYSICS_H__
#define __J1PHYSICS_H__

#include "j1Module.h"
#include "p2Point.h"
#include "j1Collision.h"
#include "p2List.h"

#define MAX_OBJECTS 15

struct object
{
	iPoint position;
	iPoint velocity;
	uint gravity;
	Collider* col;
	Collider* predictor;
};

class j1Physics : public j1Module
{
public:
	j1Physics();
	~j1Physics();

	bool PreUpdate();

	bool Awake(pugi::xml_node* config);

	object* Addobject(int x, int y, int gravity, SDL_Rect* collision,COLLIDER_TYPE TYPE, j1Module* callback);

	void OnCollision(Collider* c1, Collider* c2);
	
	bool CleanUp();

	object** objects;
};
#endif // !__J1PHYSICS_H__
