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
	// idle animation
	idle.PushBack({ 277, 3, 45, 45 });
	idle.PushBack({ 322, 3, 45, 45 });
	idle.speed = 0.2f;

	// Move Right
	right.PushBack({ 3, 3, 45, 45 });
	right.PushBack({ 48, 3, 45, 45 });
	right.PushBack({ 93, 3, 45, 45 });
	right.PushBack({ 137, 3, 45, 45 });
	right.PushBack({ 182, 3, 45, 45 });
	right.PushBack({ 227, 3, 45, 45 });
	right.speed = 0.2f;

	// Move Left
	left.PushBack({ 3, 52, 45, 45 });
	left.PushBack({ 48, 52, 45, 45 });
	left.PushBack({ 93, 52, 45, 45 });
	left.PushBack({ 137, 52, 45, 45 });
	left.PushBack({ 182, 52, 45, 45 });
	left.PushBack({ 227, 52, 45, 45 });
	left.speed = 0.2f;

	// Jumpsquat Right animation
	jumpsquatRight.PushBack({ 3, 100, 45, 45 });
	jumpsquatRight.PushBack({ 48, 100, 45, 45 });
	jumpsquatRight.PushBack({ 93, 100, 45, 45 });
	jumpsquatRight.PushBack({ 137, 100, 45, 45 });
	jumpsquatRight.PushBack({ 182, 100, 45, 45 });
	jumpsquatRight.PushBack({ 227, 100, 45, 45 });
	jumpsquatRight.PushBack({ 3, 149, 45, 45 });
	jumpsquatRight.PushBack({ 48, 149, 45, 45 });
	jumpsquatRight.speed = 0.2f;

	// Airborne Right animation
	airborneRight.PushBack({ 93, 149, 45, 45 });
	airborneRight.PushBack({ 137, 149, 45, 45 });
	airborneRight.PushBack({ 182, 149, 45, 45 });
	airborneRight.PushBack({ 227, 149, 45, 45 });
	airborneRight.speed = 0.2f;

	// Jumpsquat Left animation
	jumpsquatLeft.PushBack({ 3, 198, 45, 45 });
	jumpsquatLeft.PushBack({ 48, 198, 45, 45 });
	jumpsquatLeft.PushBack({ 93, 198, 45, 45 });
	jumpsquatLeft.PushBack({ 137, 198, 45, 45 });
	jumpsquatLeft.PushBack({ 182, 198, 45, 45 });
	jumpsquatLeft.PushBack({ 227, 198, 45, 45 });
	jumpsquatLeft.PushBack({ 3, 247, 45, 45 });
	jumpsquatLeft.PushBack({ 48, 247, 45, 45 });
	jumpsquatLeft.speed = 0.2f;

	// Airborne Left animation
	airborneLeft.PushBack({ 93, 247, 45, 45 });
	airborneLeft.PushBack({ 137, 247, 45, 45 });
	airborneLeft.PushBack({ 182, 247, 45, 45 });
	airborneLeft.PushBack({ 227, 247, 45, 45 });
	airborneLeft.speed = 0.2f;
}

bool j1Player::Awake(pugi::xml_node& config)
{
	LOG("Loading player config");
	width = config.child("size").attribute("width").as_int(20);
	height = config.child("size").attribute("height").as_int(20);
	jump_speed = config.child("acceleration").attribute("jump").as_float(-500);
	acceleration = config.child("acceleration").attribute("horizontal").as_float(0.1);
	max_speed = config.child("velocity").attribute("max").as_float(1.5);

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

	player = App->physics->Addobject(150,-200,0.025,&rect,COLLIDER_PLAYER,this);
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

