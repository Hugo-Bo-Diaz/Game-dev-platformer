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
#include "j1Player.h"
#include "j1Physics.h"

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
	App->map->Load(App->map->current_map.GetString());
	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	uint win;
	uint i;
	App->win->GetWindowSize(win, i);
	App->render->camera.x = -App->player->player->position.x + win / 2;
	if (App->render->camera.x < win / 2)
	{App->render->camera.x = 0;}
	if (-App->render->camera.x > ((App->map->data.width*App->map->data.tile_width)-win))
	{App->render->camera.x = -(App->map->data.width*App->map->data.tile_width)+win;}

	if(App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		App->LoadGame();

	if(App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		App->SaveGame();

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
	p2SString title("Where's my plane?");

	App->win->SetTitle(title.GetString());
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
