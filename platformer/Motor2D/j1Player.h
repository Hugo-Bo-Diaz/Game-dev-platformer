#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "j1Module.h"
#include "Animation.h"
#include "p2Point.h"

struct object;
struct SDL_Texture;
struct Collider;

class j1Player : public j1Module
{
public:
	j1Player();
	~j1Player();

	bool Start();
	bool PreUpdate();
	bool Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

public:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* sprites = nullptr;
	Collider* collider;
	Animation* current_animation = nullptr;

	Animation idle;
	Animation left;
	Animation right;
	Animation airborn;
	Animation jumpsquat;

	int lifes = 3;
	int initial_x = 10;
	int initial_y = 10;
	int width = 20;
	int height = 20;

	object* player;
};

#endif