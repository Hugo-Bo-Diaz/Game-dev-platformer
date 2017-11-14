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
	// Idle animation
	idle.PushBack({ 0, 0, 30, 28 });
	idle.PushBack({ 32, 0, 30, 28 });
	idle.PushBack({ 64, 0, 30, 28 });
	idle.speed = 0.04f;
	//animations.add(idle);
	//Moving left animation
	left.PushBack({ 0, 30, 18, 28 });
	left.PushBack({ 20, 30, 18, 28 });
	left.PushBack({ 40, 30, 18, 28 });
	left.PushBack({ 60, 30, 18, 28 });
	left.speed = 0.04f;
	//animations.add(left);
	//Moving right animation
	right.PushBack({ 0, 60, 18, 28 });
	right.PushBack({ 20, 60, 18, 28 });
	right.PushBack({ 40, 60, 18, 28 });
	right.PushBack({ 60, 60, 18, 28 });
	right.speed = 0.04f;
	//animations.add(right);

	current_animation = &idle;
}

void EntityEnemyBat::Start()
{
	//BROFILER_CATEGORY("Start_EntityEnemyBat", Profiler::Color::Gold);

	LOG("Loading enemy bat");
	//create object

	SDL_Rect rect;
	rect.x = App->map->initial_player_pos.x;
	rect.y = App->map->initial_player_pos.y;
	rect.w = width;
	rect.h = height;
	LoadTex("textures/Bat.png");
	obj = App->physics->Addobject(App->map->initial_player_pos.x, App->map->initial_player_pos.y,
		gravity, &rect, COLLIDER_PLAYER, (j1Module*)App->entities);
	position.x = obj->position.x;
	position.y = obj->position.y;
	destroyed = false;
	interactive = true;
}

void EntityEnemyBat::Awake()
{

}

EntityEnemyBat::~EntityEnemyBat()
{}

void EntityEnemyBat::CleanUp()
{

}

bool EntityEnemyBat::PreUpdate()
{
	return true;
}

bool EntityEnemyBat::Update(float dt)
{
	return true;
}

void EntityEnemyBat::Draw()
{

}

void EntityEnemyBat::OnCollision(Collider* c1, Collider* c2)
{

}

bool EntityEnemyBat::Save(pugi::xml_node& node) const
{
	return true;
}

bool EntityEnemyBat::Load(pugi::xml_node& node)
{
	return true;
}

void EntityEnemyBat::SetPosOrigin()
{
	obj->position.x = 0;
	obj->position.y = 0;
	obj->velocity.x = 0;
	obj->velocity.y = 0;
}