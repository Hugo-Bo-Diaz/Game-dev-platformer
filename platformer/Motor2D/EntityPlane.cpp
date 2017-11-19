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

#include "EntityPlane.h"

EntityPlane::EntityPlane()
{
	name.create("Plane");
}

void EntityPlane::Start()
{
	BROFILER_CATEGORY("Start_EntityBackground", Profiler::Color::Purple);

	LOG("Loading background entity");
	interactive = false;
}

void EntityPlane::Draw()
{
	BROFILER_CATEGORY("Draw_EntityBackground", Profiler::Color::Purple);

	App->render->Blit(App->entities->GetTex(3), position.x, position.y);
}