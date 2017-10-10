#include <math.h>
#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Audio.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Collision.h"
#include "j1Particles.h"
#include "j1Player.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;

	explosion.anim.PushBack({ 22, 46, 31, 31 });
	explosion.anim.PushBack({ 55, 46, 31, 31 });
	explosion.anim.PushBack({ 94, 46, 31, 31 });
	explosion.anim.PushBack({ 134, 46, 31, 31 });
	explosion.anim.PushBack({ 175, 46, 31, 31 });
	explosion.anim.PushBack({ 214, 45, 31, 31 });
	explosion.anim.PushBack({ 254, 46, 31, 31 });
	explosion.anim.PushBack({ 297, 46, 31, 31 });
	explosion.anim.PushBack({ 333, 43, 31, 31 }); //333 43 = +3x-100y
	explosion.anim.PushBack({ 373, 46, 31, 31 });	
	explosion.anim.loop = false;
	explosion.anim.speed = 0.15f;

	

}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("gunsmoke/particles.png");
	tnt_sound = App->audio->LoadFx("gunsmoke/tnt_explosion.wav");
	// Load particles fx particle

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles /n");
	App->textures->Unload(graphics);

	// Unload fx

	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
bool ModuleParticles::Update()
{
	if (powerup_activated == true)
	{
		shot_l.life =		SHOT_LIFE + App->player->powerup[1] * 32;
		shot_l_down.life =	SHOT_LIFE + App->player->powerup[1] * 32;
		shot_l_up.life =	SHOT_LIFE + App->player->powerup[1] * 32;
		shot_r.life =		SHOT_LIFE + App->player->powerup[1] * 32;
		shot_r_down.life =	SHOT_LIFE + App->player->powerup[1] * 32;
		shot_r_up.life =	SHOT_LIFE + App->player->powerup[1] * 32;
		laser.life =		SHOT_LIFE + App->player->powerup[1] * 32;

		powerup_activated = false;
	}

	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if(p == nullptr)
			continue;

		if(p->Update() == false)
		{
			delete p;
			//p = nullptr;    //WE CHANGED THIS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			active[i] = nullptr;
		}
		else if(SDL_GetTicks() >= p->born)
		{
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if(p->fx_played == false)
			{
				p->fx_played = true;
			}
		}
	}

	return true;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay, int xspeed, int yspeed, bool explosion_sound)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			if (xspeed != 100)
			{			
				p->speed.x = xspeed;
			}
			if (yspeed != 100)
			{
				p->speed.y = yspeed;
			}			
			
			if (explosion_sound)
			{
				App->audio->PlayFx(tnt_sound);
			}
			if(collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			active[i] = p;

			break;
		}
	}
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if(active[i] != nullptr && active[i]->collider == c1)
		{
			App->particles->AddParticle(App->particles->hitmarker, active[i]->position.x - 4, active[i]->position.y-4, COLLIDER_PARTICLE, 0);
			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) : 
anim(p.anim), position(p.position), speed(p.speed),
fx(p.fx), born(p.born), life(p.life)
{}

Particle::~Particle()
{

	if (collider != nullptr)
		collider->to_delete = true;
}

bool Particle::Update()
{
	bool ret = true;

	if(life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
		{
			if (collider != nullptr && collider->type == COLLIDER_PLAYER_SHOT)
			{
				App->particles->AddParticle(App->particles->end_of_bullet, position.x-4, position.y-4, COLLIDER_PARTICLE, 0);
			}

			ret = false;
		}
	}
	else
		if(anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	if(collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}

