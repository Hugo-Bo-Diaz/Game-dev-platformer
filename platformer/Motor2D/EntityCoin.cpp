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

#include "EntityCoin.h"

EntityCoin::EntityCoin()
{
	name.create("Coin");

	// Idle animation
	spin.PushBack({ 0, 0, 16, 16 });
	spin.speed = 1.0f;

	current_animation = &spin;
}

void EntityCoin::Start()
{
	BROFILER_CATEGORY("Start_EntityEnemyBat", Profiler::Color::Purple);

	LOG("Loading enemy bat");
	//create object

	position.x += offset_x;
	position.y += offset_y;

	SDL_Rect rect;
	rect.x = position.x;
	rect.y = position.y;
	rect.w = width;
	rect.h = height;

	col = App->collision->AddCollider(rect, COLLIDER_COIN, (j1Module*)App->entities);

	destroyed = false;
	interactive = true;
}

void EntityCoin::Awake()
{
	LOG("Loading coin config");
	int j = 0;
	int i = 0;
	for (j=0;j<App->entities->properties.count();++j)
	{
		if (App->entities->properties[j]->type == 3)
		{
			i = j;
			break;
		}
	}
	width = App->entities->properties[i++]->value;
	height = App->entities->properties[i++]->value;
	offset_x = App->entities->properties[i++]->value;
	offset_y = App->entities->properties[i++]->value;
}

void EntityCoin::Draw()
{
	BROFILER_CATEGORY("Draw_EntityCoin", Profiler::Color::Purple);

	App->render->Blit(App->entities->GetTex(5), position.x, position.y, &(current_animation->GetCurrentFrame()));
}

void EntityCoin::OnCollision(Collider* c1, Collider* c2)
{
	BROFILER_CATEGORY("OnCollision_EntityCoin", Profiler::Color::Purple);

	if (c1->type == COLLIDER_COIN && c2->type == COLLIDER_PLAYER)
	{
		destroyed = true;
		LOG("money money money money");
	}
}

void EntityCoin::CleanUp()
{
	if (col != nullptr)
	{
		col->to_delete = true;
		col = nullptr;
	}
}
