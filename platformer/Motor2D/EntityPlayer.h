#ifndef __EntityPlayer_H__
#define __EntityPlayer_H__

#include "j1Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "EntityInteractive.h"
struct object;
struct SDL_Texture;
struct Collider;

class EntityPlayer : public EntityInteractive
{
public:
	EntityPlayer();
	~EntityPlayer();

	void Start();
	bool CleanUp();
	bool PreUpdate();
	bool Update(float dt);
//	bool Update(float dt);
	void OnCollision(Collider* c1, Collider* c2);
	void Awake();

	void SetPosOrigin();// sets player to the start of the map
	
	void Draw();

	bool Save(pugi::xml_node&) const;
	bool Load(pugi::xml_node&);
	void InitialPos()
	{
		position.x = 0;
		position.y = 0;
	}

public:

	Animation idle;
	Animation left;
	Animation right;
	Animation airborneRight;
	Animation airborneLeft;
	Animation jumpsquatRight;
	Animation jumpsquatLeft;

	//default values are added if everything that sets em up is going horrible
	int lifes = 3;
	int initial_x = 10;
	int initial_y = 10;
	int width = 200;
	int height = 200;
	float jump_speed = -5;
	float acceleration = 0.1;
	float max_speed = 1;
	float gravity = 0.01;

	bool destroyed = false;
	float hability = 0.5;
};
#endif