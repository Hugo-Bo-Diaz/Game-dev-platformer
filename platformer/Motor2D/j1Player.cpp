#include "Globals.h"
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
#include "SDL/include/SDL_timer.h"

#include<stdio.h>
// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

#define HORSE_AUDIO_DURATION 7000

j1Player::j1Player()
{
	// idle animation (just the ship)
	idle.PushBack({ 4, 8, 19, 29 });
	idle.PushBack({ 25, 8, 20, 29 });
	idle.PushBack({ 48, 8, 19, 29 });
	idle.PushBack({ 70, 8, 20, 29 });
	idle.PushBack({ 91, 8, 21, 29 });
	idle.speed = 0.2f;

	// move left
	left.PushBack({ 24, 73, 16, 26 });
	left.PushBack({ 4, 74, 17, 29 });
	left.PushBack({ 242, 72, 17, 30 });
	left.PushBack({ 219, 72, 17, 30 });
	left.PushBack({ 194, 72, 21, 30 });
	left.speed = 0.2f;

	// Move right
	right.PushBack({ 218, 7, 16, 26 });
	right.PushBack({ 237, 8, 17, 29 });
	right.PushBack({ 1, 39, 17, 30 });
	right.PushBack({ 23, 39, 17, 30 });
	right.PushBack({ 45, 39, 21, 30 });
	right.speed = 0.2f;
}

j1Player::~j1Player()
{}

// Load assets
bool j1Player::Start()
{
	LOG("Loading player");

	graphics = App->tex->Load("gunsmoke/player.png");
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
bool j1Player::Update()
{
	joystick_left = 0;
	joystick_right = 0;

	float speed = 2.0;
/*
		if (App->input->controller_1.left_joystick.x > 0.25)
		{
			joystick_right = 1;
		}
		if (App->input->controller_1.left_joystick.x < -0.25)
		{
			joystick_left = 1;
		}

		joystick_down = 0;
		joystick_up = 0;

		if (App->input->controller_1.left_joystick.y > 0.25)
		{
			joystick_down = 1;
		}
		if (App->input->controller_1.left_joystick.y < -0.25)
		{
			joystick_up = 1;
		}
		*/


		if ((App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT))
		{
			position.y -= speed;
		}

		if ((App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT))
		{
			position.y += speed;
		}

		if ((App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT))
		{
			position.x += speed;
			if (current_animation != &right)
			{
				right.Reset();
				current_animation = &right;
			}

		}

		if ((App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT))
		{
			position.x -= speed;
			if (current_animation != &left)
			{
				left.Reset();
				current_animation = &left;
			}

		}



		if ((App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE)
			&& (App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE))
		{
			current_animation = &idle;
		}
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT
			&& App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			current_animation = &idle;
		}

	App->render->Blit(graphics, (int)position.x, (int)position.y, &(current_animation->GetCurrentFrame()));

	//Draw HUD(lifes / powerups)---------------------------------

	return true;
}


void j1Player::OnCollision(Collider* c1, Collider* c2)
{

	//death_time = SDL_GetTicks();

	/*if (c1 == collider && c2->type == COLLIDER_ENEMY_SHOT
		&& destroyed == false && App->fade->IsFading() == false)
	{


	}*/

}

