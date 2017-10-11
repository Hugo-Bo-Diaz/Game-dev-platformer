#include "p2Log.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Particles.h"
#include "j1Render.h"
#include "j1Collision.h"
#include "j1FadeToBlack.h"
#include "j1Player.h"
#include "j1Audio.h"
#include "j1Physics.h"
#include "SDL/include/SDL_timer.h"

#include<stdio.h>
// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

#define HORSE_AUDIO_DURATION 7000

j1Player::j1Player()
{
	name.create("player");
	// idle animation (just the ship)
	idle.PushBack({ 4, 8, 19, 29 });
	idle.speed = 0.2f;

	// move left
	left.PushBack({ 24, 73, 16, 26 });
	left.speed = 0.2f;

	// Move right
	right.PushBack({ 218, 7, 16, 26 });
	right.speed = 0.2f;
}

bool j1Player::Awake(pugi::xml_node& config)
{
	LOG("Loading player config");
	width = config.child("size").attribute("width").as_int(20);
	height = config.child("size").attribute("height").as_int(20);
	jump_speed = config.child("acceleration").attribute("jump").as_float(-500);
	acceleration = config.child("acceleration").attribute("horizontal").as_float(5);
	max_speed = config.child("velocity").attribute("max").as_float(10);

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

	player = App->physics->Addobject(150,-200,0.1,&rect,COLLIDER_PLAYER,this);
	return true;
}

// Unload assets
bool j1Player::CleanUp()
{
	LOG("Unloading player");
	App->tex->UnLoad(graphics);

	return true;
}

bool j1Player::PreUpdate()
{
	return true;
}

// Update: draw background
bool j1Player::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && player->velocity.x <max_speed)
	{
		player->acceleration.x = acceleration;
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && player->velocity.x >-max_speed)
	{
		player->acceleration.x = -acceleration;
	}
	if (player->velocity.x > max_speed || player->velocity.x < -max_speed)
	{
		player->acceleration.x = 0;
	}

		if ((App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE)
			&& (App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE))
		{
			current_animation = &idle;
			player->acceleration.x = -player->velocity.x/10;
		}
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT
			&& App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			current_animation = &idle;
			player->acceleration.x = -player->velocity.x / 10;
			player->velocity.x = 0;

		}

		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN && player->grounded)
		{
			player->velocity.y = -jump_speed;
			player->grounded = false;
		}

	//App->render->Blit(graphics, (int)player->position.x, (int)player->position.y, &(current_animation->GetCurrentFrame()));

	//Draw HUD(lifes / powerups)---------------------------------

	return true;
}


void j1Player::OnCollision(Collider* c1, Collider* c2)
{

}

