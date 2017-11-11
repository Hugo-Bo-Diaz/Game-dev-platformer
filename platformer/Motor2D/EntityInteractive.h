#ifndef _J1INTERACTIVE_H_
#define _J1INTERACTIVE_H_

#include "j1Physics.h"
#include "Entity.h"

class EntityInteractive : public Entity
{
public:
	object* obj;

public:

	EntityInteractive() {};
	EntityInteractive(float _x, float _y, float _gravity, SDL_Rect* collision, COLLIDER_TYPE TYPE)
	{
		obj->acceleration = fPoint(0, _gravity);
		obj->position = fPoint(_x, _y);
		obj->col = App->collision->AddCollider(*collision,TYPE,nullptr);
	};
	~EntityInteractive() {};

	virtual void Draw() {};
	virtual bool PreUpdate() { return true; };
	virtual bool Update(float dt) { return true; };
	virtual bool PostUpdate() { return true; };
	virtual void Awake() {};
	virtual void Start() {};
};


#endif // !
