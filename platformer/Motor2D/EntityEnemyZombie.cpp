#include "p2Log.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Collision.h"
#include "j1Map.h"
#include "j1Audio.h"
#include "j1Physics.h"
#include "j1Pathfinding.h"
#include "j1EntityManager.h"
#include "SDL/include/SDL_timer.h"
#include "Brofiler\Brofiler.h"

#include "EntityEnemyZombie.h"

EntityEnemyZombie::EntityEnemyZombie()
{
	name.create("Zombie");

	// Idle animation
	idle.PushBack({ 0, 82, 30, 38 });
	idle.PushBack({ 32, 82, 30, 38 });
	idle.PushBack({ 64, 82, 30, 38 });
	idle.speed = 0.12f;
	//animations.add(idle);
	//Moving left animation
	/*left.PushBack({ 0, 30, 18, 28 });
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
	*/
	current_animation = &idle;
}

void EntityEnemyZombie::Start()
{
	BROFILER_CATEGORY("Start_EntityEnemyZombie", Profiler::Color::Purple);

	LOG("Loading enemy Zombie");
	//create object

	SDL_Rect rect;
	rect.x = position.x;
	rect.y = position.y;
	rect.w = width;
	rect.h = height;
	obj = App->physics->Addobject(position.x, position.y,
									gravity, &rect, COLLIDER_LAVA, (j1Module*)App->entities);
	destroyed = false;
	interactive = true;
}

void EntityEnemyZombie::Awake()
{
	LOG("Loading bat config");
	int j = 0;
	int i = 0;
	for (j=0;j<App->entities->properties.count();++j)
	{
		if (App->entities->properties[j]->type == 2)
		{
			i = j;
			break;
		}
	}
	width = App->entities->properties[i++]->value;
	height = App->entities->properties[i++]->value;
	lifes = App->entities->properties[i++]->value;
	acceleration = App->entities->properties[i++]->value;
	max_speed = App->entities->properties[i++]->value;
	gravity = App->entities->properties[i++]->value;
	
}

EntityEnemyZombie::~EntityEnemyZombie()
{
	LOG("I've been deleted, ouch!");
}

void EntityEnemyZombie::CleanUp()
{
	LOG("Unloading Zombie :(");
}

bool EntityEnemyZombie::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdate_EntityEnemyZombie", Profiler::Color::Purple);

	if (destroyed == true)
	{
		//Destroy bat
	}

	return true;
}

bool EntityEnemyZombie::Update(float dt)
{
	BROFILER_CATEGORY("Update_EntityEnemyZombie", Profiler::Color::Purple);

	//CONTROLS
	obj->velocity.x = 1;
	if (obj->velocity.y == 0)
	{
		obj->velocity.y = -5;
	}
	

	position.x = obj->position.x;
	position.y = obj->position.y;

	if (abs(position.x - App->map->player->position.x) < App->map->data.tile_width * 7 && App->map->player->position.y > 6)
	{
		p2DynArray<iPoint> path;
		App->path->PropagateBFS(path, position, App->map->player->position);
	}
	//position is an easy way of telling where it is for other objects, not actually needed but useful in 
	//references and also not all entities have objects whose position is calculated automatically
	return true;
}

void EntityEnemyZombie::Draw()
{
	BROFILER_CATEGORY("Draw_EntityEnemyZombie", Profiler::Color::Purple);

	App->render->Blit(App->entities->GetTex(2), (int)obj->position.x, (int)obj->position.y+1, &(current_animation->GetCurrentFrame()));
}

void EntityEnemyZombie::OnCollision(Collider* c1, Collider* c2)
{
	BROFILER_CATEGORY("OnCollision_EntityEnemyZombie", Profiler::Color::Purple);
}