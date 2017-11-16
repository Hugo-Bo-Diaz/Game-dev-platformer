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

#include "EntityEnemyBat.h"

EntityEnemyBat::EntityEnemyBat()
{
	name.create("Bat");

	// Idle animation
	idle.PushBack({ 0, 0, 30, 28 });
	idle.PushBack({ 32, 0, 30, 28 });
	idle.PushBack({ 64, 0, 30, 28 });
	idle.speed = 0.12f;
	//animations.add(idle);
	//Moving left animation
	left.PushBack({ 0, 30, 18, 28 });
	left.PushBack({ 20, 30, 18, 28 });
	left.PushBack({ 40, 30, 18, 28 });
	left.PushBack({ 60, 30, 18, 28 });
	left.speed = 0.15f;
	//animations.add(left);
	//Moving right animation
	right.PushBack({ 0, 60, 18, 28 });
	right.PushBack({ 20, 60, 18, 28 });
	right.PushBack({ 40, 60, 18, 28 });
	right.PushBack({ 60, 60, 18, 28 });
	right.speed = 0.15f;
	//animations.add(right);

	current_animation = &idle;
}

void EntityEnemyBat::Start()
{
	BROFILER_CATEGORY("Start_EntityEnemyBat", Profiler::Color::Purple);

	LOG("Loading enemy bat");
	//create object

	SDL_Rect rect;
	rect.x = App->map->initial_player_pos.x;
	rect.y = App->map->initial_player_pos.y;
	rect.w = width;
	rect.h = height;
	obj = App->physics->Addobject(	App->map->initial_player_pos.x, App->map->initial_player_pos.y, 
									gravity, &rect, COLLIDER_LAVA, (j1Module*)App->entities);
	position.x = obj->position.x;
	position.y = obj->position.y;
	destroyed = false;
	interactive = true;
}

void EntityEnemyBat::Awake()
{
	LOG("Loading bat config");
	int i = 0;
	while (i < App->entities->properties.count() && App->entities->properties[i]->type == 1)
	{
		width = App->entities->properties[i++]->value;
		height = App->entities->properties[i++]->value;
		lifes = App->entities->properties[i++]->value;
		acceleration = App->entities->properties[i++]->value;
		max_speed = App->entities->properties[i++]->value;
		gravity = App->entities->properties[i++]->value;
	}
}

EntityEnemyBat::~EntityEnemyBat()
{
	LOG("I've been deleted, ouch!");
}

void EntityEnemyBat::CleanUp()
{
	LOG("Unloading Bat :(");
}

bool EntityEnemyBat::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdate_EntityEnemyBat", Profiler::Color::Purple);

	if (destroyed == true)
	{
		//Destroy bat
	}

	return true;
}

bool EntityEnemyBat::Update(float dt)
{
	BROFILER_CATEGORY("Update_EntityEnemyBat", Profiler::Color::Purple);

	//CONTROLS

	position.x = obj->position.x;
	position.y = obj->position.y;
	//position is an easy way of telling where it is for other objects, not actually needed but useful in 
	//references and also not all entities have objects whose position is calculated automatically
	return true;
}

void EntityEnemyBat::Draw()
{
	BROFILER_CATEGORY("Draw_EntityEnemyBat", Profiler::Color::Purple);

	App->render->Blit(App->entities->GetTex(1), (int)obj->position.x - 10, (int)obj->position.y, &(current_animation->GetCurrentFrame()));
}

void EntityEnemyBat::OnCollision(Collider* c1, Collider* c2)
{
	BROFILER_CATEGORY("OnCollision_EntityEnemyBat", Profiler::Color::Purple);
}