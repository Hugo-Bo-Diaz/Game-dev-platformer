#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Scene.h"
//#include "j1Player.h"
#include "j1Physics.h"
#include "Brofiler\Brofiler.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	BROFILER_CATEGORY("Start_Scene", Profiler::Color::LawnGreen);

	App->map->Load(App->map->current_map.GetString());
	App->audio->PlayMusic("audio/music/FindYou.ogg");
	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate(float dt)
{
	BROFILER_CATEGORY("PreUpdate_Scene", Profiler::Color::LawnGreen);

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
		App->map->player->SetPosOrigin();

	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	BROFILER_CATEGORY("Update_Scene", Profiler::Color::LawnGreen);

	uint win;
	uint i;
	App->win->GetWindowSize(win, i);
	if (App->map->player != nullptr)
	{
		App->render->camera.x = -App->map->player->position.x + win / 2;
		if (App->render->camera.x < win / 2)
		{
			App->render->camera.x = 0;
		}
		if (-App->render->camera.x > ((App->map->data.width*App->map->data.tile_width) - win))
		{
			App->render->camera.x = -(App->map->data.width*App->map->data.tile_width) + win;
		}
	}
	//DEBUG FEATURES
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		App->map->change_to_this_level = 0;

	if(App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		App->LoadGame();

	if(App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		App->SaveGame();

	if (App->input->GetKey(SDL_SCANCODE_KP_PLUS) == KEY_DOWN)
		App->audio->RiseVolume();

	if (App->input->GetKey(SDL_SCANCODE_KP_MINUS) == KEY_DOWN)
		App->audio->LowerVolume();

	//App->render->Blit(img, 0, 0);
	App->map->Draw();

	/*int _x = 0;
	int _y = 0;

	App->input->GetMousePosition(_x, _y);
	_x = (-App->render->camera.x + _x) / App->map->data.tile_width;
	_y = (-App->render->camera.y + _y) / App->map->data.tile_height;

	p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d Tile x mouse:%d Tile y mouse:%d",
					App->map->data.width, App->map->data.height,
					App->map->data.tile_width, App->map->data.tile_height,
					App->map->data.tilesets.count(),_x,_y);*/
	//p2SString title("Where's my plane?");

	//App->win->SetTitle(title.GetString());
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate(float dt)
{
	BROFILER_CATEGORY("PostUpdate_Scene", Profiler::Color::LawnGreen);

	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;



	if (App->map->change_to_next_level)
	{
		App->map->next_level();
		App->map->change_to_next_level = false;
	}

	if (App->map->change_to_previous_level)
	{
		App->map->previous_level();
		App->map->change_to_previous_level = false;
	}
	if (App->map->change_to_this_level != -1)
	{
		App->map->change_map(App->map->change_to_this_level);
		App->map->change_to_this_level = -1;
		/*App->map->player->obj->position.x = App->map->player->pos_saved_x;
		App->map->player->obj->position.y = App->map->player->pos_saved_y;*/
	}

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	BROFILER_CATEGORY("CleanUp_Scene", Profiler::Color::LawnGreen);

	LOG("Freeing scene");

	return true;
}
