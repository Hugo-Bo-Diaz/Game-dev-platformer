#include "p2Log.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Collision.h"
#include "j1Map.h"
#include "j1Audio.h"
#include "j1Physics.h"
#include "j1EntityManager.h"
#include "SDL/include/SDL_timer.h"

#include "EntityPlayer.h"

#include<stdio.h>

EntityPlayer::EntityPlayer()
{
	name.create("Player");


	// idle animation
	idle.PushBack({ 277, 3, 45, 45 });
	idle.PushBack({ 322, 3, 45, 45 });
	idle.speed = 0.04f;
	animations.add(&idle);

	// Move Right
	left.PushBack({ 3, 3, 45, 45 });
	left.PushBack({ 48, 3, 45, 45 });
	left.PushBack({ 93, 3, 45, 45 });
	left.PushBack({ 137, 3, 45, 45 });
	left.PushBack({ 182, 3, 45, 45 });
	left.PushBack({ 227, 3, 45, 45 });
	left.speed = 0.18f;
	animations.add(&left);
	// Move Left
	right.PushBack({ 3, 52, 45, 45 });
	right.PushBack({ 48, 52, 45, 45 });
	right.PushBack({ 93, 52, 45, 45 });
	right.PushBack({ 137, 52, 45, 45 });
	right.PushBack({ 182, 52, 45, 45 });
	right.PushBack({ 227, 52, 45, 45 });
	right.speed = 0.18f;
	animations.add(&right);
	// Jumpsquat Right animation

	jumpsquatRight.PushBack({ 93, 100, 45, 45 });
	jumpsquatRight.speed = 0.0f;
	animations.add(&jumpsquatRight);
	// Airborne Right animation
	airborneRight.PushBack({ 182, 149, 45, 45 });
	airborneRight.PushBack({ 227, 149, 45, 45 });
	airborneRight.speed = 0.1f;
	animations.add(&airborneRight);
	// Jumpsquat Left animation
	jumpsquatLeft.PushBack({ 93, 198, 45, 45 });
	jumpsquatLeft.speed = 0.0f;
	animations.add(&jumpsquatLeft);
	// Airborne Left animation
	airborneLeft.PushBack({ 182, 247, 45, 45 });
	airborneLeft.PushBack({ 227, 247, 45, 45 });
	airborneLeft.speed = 0.1f;
	animations.add(&airborneLeft);

	current_animation = animations.start->data;


}

void EntityPlayer::Start()
{
	LOG("Loading player");
	//create object

	SDL_Rect rect;
	rect.x = initial_x;
	rect.y = initial_y;
	rect.w = width;
	rect.h = height;
	LoadTex("textures/PilotSprites.png");
	obj = App->physics->Addobject(initial_x, initial_y, gravity, &rect, COLLIDER_PLAYER);
	destroyed = false;
}
void EntityPlayer::Awake()
{
	LOG("Loading player config");
/*	width = config.child("size").attribute("width").as_int(20);
	height = config.child("size").attribute("height").as_int(20);
	jump_speed = config.child("acceleration").attribute("jump").as_float(-500);
	acceleration = config.child("acceleration").attribute("horizontal").as_float(0.1);
	max_speed = config.child("velocity").attribute("max").as_float(1.5);
	gravity = config.child("gravity").attribute("value").as_float(0.03);
	hability = config.child("hability").attribute("value").as_float(0.2);*/
	int lmao = App->entities->properties.start->data.value;
}

EntityPlayer::~EntityPlayer()
{}

// Unload assets
bool EntityPlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
bool EntityPlayer::Update(float dt)
{
	//CONTROLS
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && obj->velocity.x <max_speed)
	{
		obj->acceleration.x = acceleration;
		//player->velocity.x = max_speed-1;
		current_animation = &left;
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && obj->velocity.x >-max_speed)
	{
		obj->acceleration.x = -acceleration;
		//player->velocity.x = max_speed + 1;

		current_animation = &right;
	}
	if (obj->velocity.x > max_speed || obj->velocity.x < -max_speed)
	{
		obj->acceleration.x = 0;
	}

	if ((App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE)
		&& (App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE))
	{
		current_animation = &idle;
		obj->velocity.x = 0; //this stops the player
		obj->acceleration.x = 0;
		LOG("%d", obj->velocity.x);
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT
		&& App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		current_animation = &idle;
		obj->velocity.x = 0; //this stops the player
		obj->acceleration.x = 0;
	}

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN && obj->grounded && obj->velocity.y < 0.5)
	{
		obj->velocity.y = -jump_speed;
		obj->grounded = false;
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		obj->velocity.y = -hability;
	}


	//aereal animations
	if (obj->grounded == false)
	{
		if (obj->velocity.y < 0)
		{
			if (obj->velocity.x < 0)
				current_animation = &jumpsquatLeft;
			if (obj->velocity.x >= 0)
				current_animation = &jumpsquatRight;
		}
		else
		{
			if (obj->velocity.x < 0)
				current_animation = &airborneLeft;
			if (obj->velocity.x >= 0)
				current_animation = &airborneRight;
		}
	}
	//blit

	return true;
}

void EntityPlayer::Draw()
{
	App->render->Blit(texture, (int)obj->position.x - 10, (int)obj->position.y, &(current_animation->GetCurrentFrame()));

}

bool EntityPlayer::PreUpdate()
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

void EntityPlayer::OnCollision(Collider* c1, Collider* c2)
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

bool EntityPlayer::Save(pugi::xml_node& node) const
{
	pugi::xml_node pos = node.append_child("position");

	pos.append_attribute("x") = obj->position.x;
	pos.append_attribute("y") = obj->position.y;
	pos.append_attribute("current_map") = App->map->index_map;

	return true;
}

bool EntityPlayer::Load(pugi::xml_node& node)
{
	App->map->change_map(node.child("position").attribute("current_map").as_uint());
	obj->position.x = node.child("position").attribute("x").as_int();
	obj->position.y = node.child("position").attribute("y").as_int();
	obj->velocity.x = 0;
	obj->velocity.y = 0;

	return true;
}

void EntityPlayer::SetPosOrigin()
{
	obj->position.x = initial_x;
	obj->position.y = initial_y;
	obj->velocity.x = 0;
	obj->velocity.y = 0;
}