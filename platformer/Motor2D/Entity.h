#ifndef __J1ENTITY_H__
#define __J1ENTITY_H__

#include "p2Point.h"
#include "j1Textures.h"

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
public:
	virtual void Draw() {};
	ENTITY_TYPE Get_type()
	{
		return type;
	}
	virtual void update() {};

};
#endif // !__J1ENTITY_H__
