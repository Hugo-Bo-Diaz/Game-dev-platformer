#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "j1Window.h"

#include "UItext.h"
#include "UIimage.h"
#include "UIbutton.h"
#include "UICheckBox.h"
#include "UItextbox.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());

	return true;
}

// Update all guis
bool j1Gui::PreUpdate(float dt)
{
	p2List_item<UIelement*>* item = elements.start;
	bool ret = true;
	while (item != NULL)
	{
		if (MouseInside(&item->data->GetRect()))
		{
			item->data->OnMouseOver();
			if (App->input->GetMouseButtonDown(1) == KEY_DOWN)//left click
			{
				item->data->OnClick();
			}
		}
		if (App->input->GetMouseButtonDown(1) == KEY_UP)
		{
			if (ret == true)
				ret = item->data->OnRelease();

		}
		item = item->next;
	}

	return ret;
}

// Called after all Updates
bool j1Gui::PostUpdate(float dt)
{
	p2List_item<UIelement*>* item = elements.start;

	while (item !=NULL)
	{
		item->data->Draw();
		item = item->next;
	}
	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	p2List_item<UIelement*>* item = elements.start;

	while (item != NULL)
	{
		RELEASE(item->data);
		item = item->next;
	}
	elements.clear();

	return true;
}

// const getter for atlas
SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

bool j1Gui::MouseInside(SDL_Rect* rect)
{
	int x = 0;
	int y = 0;
	App->input->GetMousePosition(x, y);
	if (x < (rect->x + rect->w) && x > rect->x &&y < (rect->y + rect->h) && y > rect->y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// class Gui ---------------------------------------------------

UIelement* j1Gui::GUIAdd_text(int x, int y, const char* text, SDL_Color color, _TTF_Font* font)
{
	iPoint pos = { x,y };
	UIelement* ret = new UItext(pos,text, color, font);
	elements.add(ret);
	return ret;
}

UIelement* j1Gui::GUIAdd_button(int x, int y, SDL_Rect portion, const char* text, button_type type)
{
	iPoint pos = { x,y };
	UIelement* ret = new UIButton(pos, text, type, portion);
	elements.add(ret);
	return ret;
}

UIelement* j1Gui::GUIAdd_image(int x, int y, SDL_Rect portion)
{
	iPoint pos = { x,y };
	UIelement* ret = new UIimage(pos, portion);
	elements.add(ret);
	return ret;
}

UIelement* j1Gui::GUIAdd_checkbox(int x, int y, SDL_Rect portion, const char* text)
{
	iPoint pos = { x,y };
	UIelement* ret = new UICheckBox(pos,text);
	elements.add(ret);
	return ret;
}

UIelement* j1Gui::GUIAdd_textbox(int x, int y, const char* title)
{
	iPoint pos = { x,y };
	UIelement* ret = new UICheckBox(pos, title);
	elements.add(ret);
	return ret;
}
