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
#include "Brofiler\Brofiler.h"

#include "EntityPlayer.h"

#include<stdio.h>

EntityPlayer::EntityPlayer()
{
	name.create("Player");


	// idle animation
	idle.PushBack({ 277, 3, 45, 45 });
	idle.PushBack({ 322, 3, 45, 45 });
	idle.speed = 0.04f;
	animations.add(idle);

	// Move Right
	left.PushBack({ 3, 3, 45, 45 });
	left.PushBack({ 48, 3, 45, 45 });
	left.PushBack({ 93, 3, 45, 45 });
	left.PushBack({ 137, 3, 45, 45 });
	left.PushBack({ 182, 3, 45, 45 });
	left.PushBack({ 227, 3, 45, 45 });
	left.speed = 0.18f;
	animations.add(left);
	// Move Left
	right.PushBack({ 3, 52, 45, 45 });
	right.PushBack({ 48, 52, 45, 45 });
	right.PushBack({ 93, 52, 45, 45 });
	right.PushBack({ 137, 52, 45, 45 });
	right.PushBack({ 182, 52, 45, 45 });
	right.PushBack({ 227, 52, 45, 45 });
	right.speed = 0.18f;
	animations.add(right);
	// Jumpsquat Right animation

	jumpsquatRight.PushBack({ 93, 100, 45, 45 });
	jumpsquatRight.speed = 0.0f;
	animations.add(jumpsquatRight);
	// Airborne Right animation
	airborneRight.PushBack({ 182, 149, 45, 45 });
	airborneRight.PushBack({ 227, 149, 45, 45 });
	airborneRight.speed = 0.1f;
	animations.add(airborneRight);
	// Jumpsquat Left animation
	jumpsquatLeft.PushBack({ 93, 198, 45, 45 });
	jumpsquatLeft.speed = 0.0f;
	animations.add(jumpsquatLeft);
	// Airborne Left animation
	airborneLeft.PushBack({ 182, 247, 45, 45 });
	airborneLeft.PushBack({ 227, 247, 45, 45 });
	airborneLeft.speed = 0.1f;
	animations.add(airborneLeft);

	current_animation = &animations.start->data;


}

void EntityPlayer::Start()
{
	BROFILER_CATEGORY("Start_EntityPlayer", Profiler::Color::Gold);

	LOG("Loading player");
	//create object

	SDL_Rect rect;
	rect.x = App->map->initial_player_pos.x;
	rect.y = App->map->initial_player_pos.y;
	rect.w = width;
	rect.h = height;
	LoadTex("textures/PilotSprites.png");
	obj = App->physics->Addobject(	App->map->initial_player_pos.x, App->map->initial_player_pos.y, 
									gravity, &rect, COLLIDER_PLAYER, (j1Module*)App->entities);
	position.x = obj->position.x;
	position.y = obj->position.y;
	destroyed = false;
	interactive = true;
}

void EntityPlayer::Awake()
{
	LOG("Loading player config");
	int i = 0;
	while (i < App->entities->properties.count() && App->entities->properties[i]->type == 0)
	{
		width = App->entities->properties[i++]->value;
		height = App->entities->properties[i++]->value;
		lifes = App->entities->properties[i++]->value;
		jump_speed = App->entities->properties[i++]->value;
		acceleration = App->entities->properties[i++]->value;
		max_speed = App->entities->properties[i++]->value;
		gravity = App->entities->properties[i++]->value;
		hability = App->entities->properties[i++]->value;
	}
}

EntityPlayer::~EntityPlayer()
{}

// Unload assets
void EntityPlayer::CleanUp()
{
	LOG("Unloading player");
	App->tex->UnLoad(texture);
	

}

// Update: draw background
bool EntityPlayer::Update(float dt)
{
	BROFILER_CATEGORY("Update_EntityPlayer", Profiler::Color::Gold);

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
	//this is the position inherited from enitity and allows for easy access in not precise calculus
	position.x = obj->position.x;
	position.y = obj->position.y;

	return true;
}

void EntityPlayer::Draw()
{
	BROFILER_CATEGORY("Draw_EntityPlayer", Profiler::Color::Gold);

	App->render->Blit(texture, (int)obj->position.x - 10, (int)obj->position.y, &(current_animation->GetCurrentFrame()));

}

bool EntityPlayer::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdate_EntityPlayer", Profiler::Color::Gold);

	if (destroyed == true)
	{
		SetPosOrigin();
		destroyed = false;
	}
	return true;
}

void EntityPlayer::OnCollision(Collider* c1, Collider* c2)
{
	BROFILER_CATEGORY("OnCollision_EntityPlayer", Profiler::Color::Gold);

	if (c1->type == COLLIDER_PLAYER &&c2->type == COLLIDER_NEXT_LEVEL)
	{
		App->map->change_to_next_level = true;
	}
	if (c1->type == COLLIDER_PLAYER &&c2->type == COLLIDER_LAVA)
	{
		destroyed = true;
	}
}

bool EntityPlayer::Save(pugi::xml_node& node) const
{
	BROFILER_CATEGORY("Save_EntityPlayer", Profiler::Color::Gold);

	pugi::xml_node player = node.append_child("Player");
	//pugi::xml_node pos = node.append_child("position");
	player.append_attribute("x") = obj->position.x;
	player.append_attribute("y") = obj->position.y;
	player.append_attribute("current_map") = App->map->index_map;

	return true;
}

bool EntityPlayer::Load(pugi::xml_node& node)
{
	BROFILER_CATEGORY("Load_EntityPlayer", Profiler::Color::Gold);

	pugi::xml_node player_node = node.child("Player");
	App->map->change_to_this_level = player_node.attribute("current_map").as_uint();
	App->map->initial_player_pos.x = player_node.attribute("x").as_uint();
	App->map->initial_player_pos.y = player_node.attribute("y").as_uint();
	//node.child("Player").child("position").attribute("x").as_int();
	return true;
}

void EntityPlayer::SetPosOrigin()
{
	obj->position.x = App->map->player_start_in_map.x;
	obj->position.y = App->map->player_start_in_map.y;
	obj->velocity.x = 0;
	obj->velocity.y = 0;
}