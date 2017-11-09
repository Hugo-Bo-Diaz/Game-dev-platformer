#ifndef __J1ENTITY_H__
#define __J1ENTITY_H__

#include "p2Point.h"
#include "j1Textures.h"
#include "Animation.h"
#include "p2List.h"
#include "j1Physics.h"

enum ENTITY_TYPE
{
	BACKGROUND,
	MOVING_BACKGROUND,
	PLAYER,
	ENEMY
};

class Entity
{
public:
	iPoint position;
	SDL_Texture* texture;
	bool interactive;
	ENTITY_TYPE type;
	p2List<Animation> animations;
public:
	
	Entity() {};
	~Entity() {};
	
	virtual void Draw() {};
	ENTITY_TYPE Get_type()
	{
		return type;
	}
	virtual void PreUpdate() {};
	virtual void Update() {};
	virtual void PostUpdate() {};

};
#endif // !__J1ENTITY_H__
