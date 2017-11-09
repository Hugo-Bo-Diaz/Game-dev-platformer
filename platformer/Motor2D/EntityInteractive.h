#ifndef _J1INTERACTIVE_H_
#define _J1INTERACTIVE_H_

#include "j1Physics.h"
#include "Entity.h"

class EntityInteractive : public Entity
{
public:
	object* obj;

public:

	EntityInteractive(float _x, float _y, float _gravity, SDL_Rect* collision, COLLIDER_TYPE TYPE, j1Module* Callback);
	~EntityInteractive() {};

	virtual void Draw() {};
	virtual void PreUpdate() {};
	virtual void Update() {};
	virtual void PostUpdate() {};

};


#endif // !
