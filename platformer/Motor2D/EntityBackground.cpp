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

#include "EntityBackground.h"

EntityBackground::EntityBackground()
{
	name.create("background");
	interactive = false;
}

void EntityBackground::Start()
{
	BROFILER_CATEGORY("Start_EntityEnemyBat", Profiler::Color::Purple);

	LOG("Loading background entity");
	//create object
	interactive = false;
}

void EntityBackground::CleanUp()
{
	LOG("Unloading background :(");
}

bool EntityBackground::Update(float dt, bool logic)
{
	BROFILER_CATEGORY("Update_Background", Profiler::Color::Purple);

	
	return true;
}

void EntityBackground::Draw()
{
	BROFILER_CATEGORY("Draw_EntityEnemyBat", Profiler::Color::Purple);

	App->render->Blit(App->entities->GetTex(1), (int)obj->position.x - 10, (int)obj->position.y, &(current_animation->GetCurrentFrame()));
}