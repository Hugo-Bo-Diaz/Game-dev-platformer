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
#include "j1Physics.h"
#include "j1Transition.h"
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

	time_left = App->map->time_left();

	if (time_left < 0 && !App->map->timer.paused)
	{
		//LOG("TIME'S UP BIACH");
	}

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
		App->map->change_to_this_level = App->map->index_map;

	if (lifes <= 0)//reset stats NEEDS TO BE LOADED IN CONFIG, MyBad WorkInProgress
	{
		LOG("LOL U BAD");
		score = 0;
		coins = 0;
		lifes = 3;
	}

	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	BROFILER_CATEGORY("Update_Scene", Profiler::Color::LawnGreen);

	if (App->map->player != nullptr)
	{
		if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
		{
			godmode = !godmode;
			if (godmode)
			{
				App->map->player->hability = 7;
			}
			else
			{
				App->map->player->hability = App->map->player->hability_stored;
			}
		}

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
	if (!App->paused_game)
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

	if (App->paused_game && pause_background != nullptr )
	{
		uint x; uint y;
		App->win->GetWindowSize(x, y);
		App->render->Blit(pause_background,-App->render->camera.x,-App->render->camera.y);
		App->render->DrawQuad({ -App->render->camera.x,-App->render->camera.y,(int)x,(int)y }, 0, 0, 0, 50);
	}
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate(float dt)
{
	BROFILER_CATEGORY("PostUpdate_Scene", Profiler::Color::LawnGreen);

	bool ret = true;

	//if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	//	ret = false;


	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	BROFILER_CATEGORY("CleanUp_Scene", Profiler::Color::LawnGreen);

	LOG("Freeing scene");

	return true;
}

bool j1Scene::UIinteraction(UIelement* element)
{
	bool ret = true;
	UIButton* button = (UIButton*)element;
	switch (button->type)
	{
	case CONTINUE:
	{App->ResumeGame();
	break; }
	case EXIT:
	{
		if (App->transition->StartTransition())
		{
			App->map->change_to_this_level = 0;
			App->ResumeGame();
		}
	break; }
	default:
	{LOG("ERROR");
	break; }
	}
	return ret;
}

bool j1Scene::Pause()
{
	/*Continue = (UIButton*)App->gui->GUIAdd_button(200, 100, { 120, 163, 117, 52 },this,"CONTINUE",CONTINUE);//{1,143,143,71}
	Exit = (UIButton*)App->gui->GUIAdd_button(200, 200, { 0, 0, 117, 52 },this,"EXIT", EXIT);//{144,143,143,71}*/
	
	Continue = (UIButton*)App->gui->GUIAdd_button(-App->render->camera.x+200, 100, {0,0,143,71},this,"CONTINUE",CONTINUE);
	Exit = (UIButton*)App->gui->GUIAdd_button(-App->render->camera.x+200, 200, {0,0,143,71},this,"EXIT", EXIT);
	
	SDL_Surface *sshot = SDL_CreateRGBSurface(0, 750, 420, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	SDL_RenderReadPixels(App->render->renderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
	pause_background = App->tex->LoadSurface(sshot);
	SDL_FreeSurface(sshot);
	sshot = nullptr;

	return true;
}
bool j1Scene::Resume()
{
	if (Continue != nullptr)
	{
		App->gui->delete_element(Continue);
		Continue = nullptr;
	}
	if (Exit != nullptr)
	{
		App->gui->delete_element(Exit);
		Exit = nullptr;
	}

	if (pause_background != nullptr)
	{
		App->tex->UnLoad(pause_background);
		pause_background = nullptr;
	}

	return true;
}