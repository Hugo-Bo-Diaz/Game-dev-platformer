#include "p2Log.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Collision.h"
#include "j1Map.h"
#include "j1Player.h"
#include "j1Audio.h"
#include "j1Physics.h"
#include "SDL/include/SDL_timer.h"

#include<stdio.h>

j1Player::j1Player()
{
	name.create("player");
	// idle animation
	idle.PushBack({ 277, 3, 45, 45 });
	idle.PushBack({ 322, 3, 45, 45 });
	idle.speed = 0.04f;

	// Move Right
	left.PushBack({ 3, 3, 45, 45 });
	left.PushBack({ 48, 3, 45, 45 });
	left.PushBack({ 93, 3, 45, 45 });
	left.PushBack({ 137, 3, 45, 45 });
	left.PushBack({ 182, 3, 45, 45 });
	left.PushBack({ 227, 3, 45, 45 });
	left.speed = 0.18f;

	// Move Left
	right.PushBack({ 3, 52, 45, 45 });
	right.PushBack({ 48, 52, 45, 45 });
	right.PushBack({ 93, 52, 45, 45 });
	right.PushBack({ 137, 52, 45, 45 });
	right.PushBack({ 182, 52, 45, 45 });
	right.PushBack({ 227, 52, 45, 45 });
	right.speed = 0.18f;

	// Jumpsquat Right animation
	/*jumpsquatRight.PushBack({ 3, 100, 45, 45 });
	jumpsquatRight.PushBack({ 48, 100, 45, 45 });*/
	jumpsquatRight.PushBack({ 93, 100, 45, 45 });
	//jumpsquatRight.PushBack({ 137, 100, 45, 45 });
	/*jumpsquatRight.PushBack({ 182, 100, 45, 45 });
	jumpsquatRight.PushBack({ 227, 100, 45, 45 });
	jumpsquatRight.PushBack({ 3, 149, 45, 45 });
	jumpsquatRight.PushBack({ 48, 149, 45, 45 });*/
	jumpsquatRight.speed = 0.0f;

	// Airborne Right animation
	/*airborneRight.PushBack({ 93, 149, 45, 45 });
	airborneRight.PushBack({ 137, 149, 45, 45 });*/
	airborneRight.PushBack({ 182, 149, 45, 45 });
	airborneRight.PushBack({ 227, 149, 45, 45 });
	airborneRight.speed = 0.1f;

	// Jumpsquat Left animation
	/*jumpsquatLeft.PushBack({ 3, 198, 45, 45 });
	jumpsquatLeft.PushBack({ 48, 198, 45, 45 });*/
	jumpsquatLeft.PushBack({ 93, 198, 45, 45 });
	//jumpsquatLeft.PushBack({ 137, 198, 45, 45 });
	/*jumpsquatLeft.PushBack({ 182, 198, 45, 45 });
	jumpsquatLeft.PushBack({ 227, 198, 45, 45 });
	jumpsquatLeft.PushBack({ 3, 247, 45, 45 });
	jumpsquatLeft.PushBack({ 48, 247, 45, 45 });*/
	jumpsquatLeft.speed = 0.0f;

	// Airborne Left animation
	/*airborneLeft.PushBack({ 93, 247, 45, 45 });
	airborneLeft.PushBack({ 137, 247, 45, 45 });*/
	airborneLeft.PushBack({ 182, 247, 45, 45 });
	airborneLeft.PushBack({ 227, 247, 45, 45 });
	airborneLeft.speed = 0.1f;
}

bool j1Player::Awake(pugi::xml_node& config)
{
	LOG("Loading player config");
	width = config.child("size").attribute("width").as_int(20);
	height = config.child("size").attribute("height").as_int(20);
	jump_speed = config.child("acceleration").attribute("jump").as_float(-500);
	acceleration = config.child("acceleration").attribute("horizontal").as_float(0.1);
	max_speed = config.child("velocity").attribute("max").as_float(1.5);
	gravity = config.child("gravity").attribute("value").as_float(0.03);
	hability = config.child("hability").attribute("value").as_float(0.2);

	return true;
}

j1Player::~j1Player()
{}

// Load assets
bool j1Player::Start()
{
	LOG("Loading player");
	//create object
	
	SDL_Rect rect;
		rect.x = initial_x;
		rect.y = initial_y;
		rect.w = width;
		rect.h = height;
	graphics = App->tex->Load("textures/PilotSprites.png");
	current_animation = &idle;
	player = App->physics->Addobject(initial_x,initial_y,gravity,&rect,COLLIDER_PLAYER,this);
	destroyed = false;
	return true;
}

// Unload assets
bool j1Player::CleanUp()
{
	LOG("Unloading player");
	App->tex->UnLoad(graphics);

	return true;
}

// Update: draw background
bool j1Player::Update(float dt)
{
	//CONTROLS
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && player->velocity.x <max_speed)
	{
		player->acceleration.x = acceleration;
		//player->velocity.x = max_speed-1;
		current_animation = &left;
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && player->velocity.x >-max_speed)
	{
		player->acceleration.x = -acceleration;
		//player->velocity.x = max_speed + 1;

		current_animation = &right;
	}
	if (player->velocity.x > max_speed || player->velocity.x < -max_speed)
	{
		player->acceleration.x = 0;
	}

	if ((App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE)
		&& (App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE))
	{
		current_animation = &idle;
		player->velocity.x = 0; //this stops the player
		player->acceleration.x = 0;
		LOG("%d", player->velocity.x);
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT
		&& App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		current_animation = &idle;
		player->velocity.x = 0; //this stops the player
		player->acceleration.x = 0;
	}

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN && player->grounded && player->velocity.y < 0.5)
	{
		player->velocity.y = -jump_speed;
		player->grounded = false;
	}
	
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		player->velocity.y = -hability;
	}


	//aereal animations
	if (player->grounded == false)
	{
		if (player->velocity.y < 0)
		{
			if (player->velocity.x < 0)
			current_animation = &jumpsquatLeft;
			if (player->velocity.x >= 0)			
			current_animation = &jumpsquatRight;
		}
		else
		{
			if (player->velocity.x < 0)
				current_animation = &airborneLeft;
			if (player->velocity.x >= 0)
				current_animation = &airborneRight;
		}
	}
	//blit
	App->render->Blit(graphics, (int)player->position.x - 10, (int)player->position.y, &(current_animation->GetCurrentFrame()));

	return true;
}

bool j1Player::PreUpdate()
{
	//DEBUG FEATURES
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		App->map->change_map(0);
	}
	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		SetPosOrigin();
	}
	if (destroyed == true)
	{
		SetPosOrigin();
		destroyed = false;
	}
	return true;
}

void j1Player::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->type == COLLIDER_PLAYER &&c2->type == COLLIDER_NEXT_LEVEL)
	{
		App->map->next_level();
	}
	if (c1->type == COLLIDER_PLAYER &&c2->type == COLLIDER_LAVA)
	{
		destroyed = true;
	}
}

bool j1Player::Save(pugi::xml_node& node) const
{
	pugi::xml_node pos = node.append_child("position");

	pos.append_attribute("x") = player->position.x;
	pos.append_attribute("y") = player->position.y;
	pos.append_attribute("current_map") = App->map->index_map;

	return true;
}

bool j1Player::Load(pugi::xml_node& node)
{
	App->map->change_map(node.child("position").attribute("current_map").as_uint());
	player->position.x = node.child("position").attribute("x").as_int();
	player->position.y = node.child("position").attribute("y").as_int();
	player->velocity.x = 0;
	player->velocity.y = 0;	

	return true;
}

void j1Player::SetPosOrigin()
{
	player->position.x = initial_x;
	player->position.y = initial_y;
	player->velocity.x = 0;
	player->velocity.y = 0;
}