#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Gui.h"
#include "j1SceneMenu.h"
#include "j1Physics.h"
#include "j1Transition.h"
#include "Brofiler\Brofiler.h"

#include "UIwindow.h"

j1SceneMenu::j1SceneMenu() : j1Module()
{
	name.create("scene");
}

// Destructor
j1SceneMenu::~j1SceneMenu()
{}

// Called before render is available
bool j1SceneMenu::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1SceneMenu::Start()
{
	BROFILER_CATEGORY("Start_Scene", Profiler::Color::LawnGreen);

	App->map->Load(App->map->maps.start->data.GetString());
	App->audio->PlayMusic("audio/music/FindYou.ogg");

	UIwindow* start_menu = (UIwindow*)App->gui->GUIAdd_window(340, 70, { 282,0,210,300 }, "MENU");
	start_menu->Attach(App->gui->GUIAdd_button(0, 0, { 0,0,143,73 }, { 144,1,133,71 }, { 0,74,171,99 }, this, "NEW GAME", button_type::NEW_GAME), { 35,35 });
	start_menu->Attach(App->gui->GUIAdd_button(0, 0, { 0,0,143,73 }, { 144,1,133,71 }, { 0,74,171,99 }, this, "LOAD GAME", button_type::LOAD_GAME), { 35,117 });
	start_menu->Attach(App->gui->GUIAdd_button(0, 0, { 0,0,143,73 }, { 144,1,133,71 }, { 0,74,171,99 }, this, "SETTINGS", button_type::SETTINGS), { 35,200 });

	App->gui->GUIAdd_button(545, 350, { 0,0,143,73 }, { 144,1,133,71 }, { 0,74,171,99 }, this, "CREDITS", button_type::CREDITS);

	App->gui->GUIAdd_button(0, 350, { 0,0,143,73 }, { 144,1,133,71 }, { 0,74,171,99 }, this, "QUIT", button_type::QUIT);

	App->gui->GUIAdd_image(10, 10, { 0,171,270,131 });

	return true;
}

// Called each loop iteration
bool j1SceneMenu::PreUpdate(float dt)
{
	BROFILER_CATEGORY("PreUpdate_Scene", Profiler::Color::LawnGreen);

	return true;
}

// Called each loop iteration
bool j1SceneMenu::Update(float dt)
{
	BROFILER_CATEGORY("Update_Scene", Profiler::Color::LawnGreen);

	App->map->Draw();

	return true;
}

// Called each loop iteration
bool j1SceneMenu::PostUpdate(float dt)
{
	BROFILER_CATEGORY("PostUpdate_Scene", Profiler::Color::LawnGreen);

	bool ret = true;

	return ret;
}

// Called before quitting
bool j1SceneMenu::CleanUp()
{
	BROFILER_CATEGORY("CleanUp_Scene", Profiler::Color::LawnGreen);

	LOG("Freeing scene");

	return true;
}


bool j1SceneMenu::UIinteraction(UIelement* element)
{
	bool ret = true;
	if (element->type_of_element == BUTTON)
	{
		UIButton* button = (UIButton*)element;
		switch (button->type)
		{
		case NEW_GAME:
		{LOG("Starting a new game");
		if (App->transition->StartTransition((j1Module*)App->level, this))
		{
			App->map->change_to_next_level = true;
		}
		break; }
		case LOAD_GAME:
		{LOG("Previously on Where is my plane...");
		if (App->transition->StartTransition((j1Module*)App->level,this))
			App->LoadGame();
		break; }
		case SETTINGS:
		{LOG("SETTINGS MENU OPENED");
		Window_menu = (UIwindow*)App->gui->GUIAdd_window(200, 150, { 494,0,210,194 }, "SETTINGS", true);
		Window_menu->Attach(App->gui->GUIAdd_slider(0, 0, { 0,0,200,45 }, { 207,116,25,43 }, { 251,116,25,43 }, { 232,134,18,9 }, { 185,112,19,42 }, 128, &App->audio->volume, "Music volume"), { 5, 60 });
		break; }
		case CREDITS:
		{
			LOG("CREDITS MENU OPENED");
			if (Window_menu == nullptr)
			{
				Window_menu = (UIwindow*)App->gui->GUIAdd_window(200, 100, { 282,0,210,300 }, "CREDITS", true);
				Window_menu->Attach(App->gui->GUIAdd_text(0, 0, "Game created by:", { 50, 50, 50, 255 }), { 20, 40 });
				Window_menu->Attach(App->gui->GUIAdd_text(0, 0, "Hugo Bó", { 50, 50, 50, 255 }), { 20, 65 });
				Window_menu->Attach(App->gui->GUIAdd_text(0, 0, "Albert Mas", { 50, 50, 50, 255 }), { 20, 85 });
				Window_menu->Attach(App->gui->GUIAdd_text(0, 0, "Art and music by:", { 50, 50, 50, 255 }), { 20, 120 });
				Window_menu->Attach(App->gui->GUIAdd_text(0, 0, "www.opengameart.org", { 50, 50, 50, 255 }), { 20, 145 });
				Window_menu->Attach(App->gui->GUIAdd_text(0, 0, "www.tannerhelland.com", { 50, 50, 50, 255 }), { 20, 165 });
				Window_menu->Attach(App->gui->GUIAdd_text(0, 0, "MIT License", { 50, 50, 50, 255 }), { 20, 200 });
				Window_menu->Attach(App->gui->GUIAdd_text(0, 0, "Copyright (c) 2017 Hugo Bó,", { 50, 50, 50, 255 }), { 20, 220 });
				Window_menu->Attach(App->gui->GUIAdd_text(0, 0, "Albert Mas", { 50, 50, 50, 255 }), { 20, 240 });
			}
			break;
		}
		case QUIT:
		{ret = false;
		break; }
		default:
		{LOG("ERROR");
		break; }
		}
	}
	return ret;
}