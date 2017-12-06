#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "j1Window.h"
#include "j1Transition.h"
#include "j1Map.h"

#include "UItext.h"
#include "UIimage.h"
#include "UIbutton.h"
#include "UICheckBox.h"
#include "UItextbox.h"
#include "UIwindow.h"
#include "UIVarDisplay.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{
	App->tex->UnLoad(atlas);
}

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
	if (App->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN)
		debug = !debug;
	
	bool item_has_been_activated = false;
	bool ret = true;

	p2List_item<UIelement*>* item = elements.end;
	while (item != NULL)
	{
		if (MouseInside(&item->data->GetRect())&& !item_has_been_activated)
		{
			item->data->mouseover = true;
			item_has_been_activated = true;
		}
		if (App->input->GetMouseButtonDown(1) == KEY_DOWN)//left click
		{
			item->data->OnClick();
		}
		if (App->input->GetMouseButtonDown(1) == KEY_UP)
		{
			if (ret == true)
			ret = item->data->OnRelease();
		}
		item = item->prev;
	}
	return ret;
}

// Called after all Updates
bool j1Gui::PostUpdate(float dt)
{
	p2List_item<UIelement*>* item = elements.start;

	while (item !=NULL)
	{		
		item->data->Update();
		if (item->data->attached_elements.count() != 0)
		{
			item->data->UpdateAttached();
		}
		item->data->Draw();
		item = item->next;
	}

	if (debug)
		UIDebugDraw();

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
	x -= App->render->camera.x;
	y -= App->render->camera.y;
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

UIelement* j1Gui::GUIAdd_text(int x, int y, const char* text, SDL_Color color,bool follow_camera, _TTF_Font* font)
{
	iPoint pos = { x,y };
	UIelement* ret = new UItext(pos,text, color,follow_camera, font);
	elements.add(ret);
	ret->Start();
	return ret;
}

UIelement* j1Gui::GUIAdd_button(int x, int y, SDL_Rect portion, SDL_Rect pressed, SDL_Rect hover, j1Module* callback, const char* text, button_type type)
{
	iPoint pos = { x,y };
	UIelement* ret = new UIButton(pos, text, type, portion,pressed,hover);
	ret->callback = callback;
	elements.add(ret);
	ret->Start();
	return ret;
}

UIelement* j1Gui::GUIAdd_image(int x, int y, SDL_Rect portion, bool follow_camera)
{
	iPoint pos = { x,y };
	UIelement* ret = new UIimage(pos, portion,follow_camera);
	elements.add(ret);
	ret->Start();
	return ret;
}

UIelement* j1Gui::GUIAdd_checkbox(int x, int y, SDL_Rect portion, j1Module* callback, const char* text)
{
	iPoint pos = { x,y };
	UIelement* ret = new UICheckBox(pos,text);
	ret->callback = callback;
	elements.add(ret);
	ret->Start();
	return ret;
}

UIelement* j1Gui::GUIAdd_textbox(int x, int y, j1Module* callback, const char* title, const char* default_text)
{
	iPoint pos = { x,y };
	UIelement* ret = new UITextbox(pos, title,default_text);
	ret->callback = callback;
	elements.add(ret);
	ret->Start();
	return ret;
}

UIelement* j1Gui::GUIAdd_window(int x, int y, SDL_Rect portion, const char* title, bool close_button)
{
	iPoint pos = { x,y };
	UIelement* ret = new UIwindow(pos, title,portion, close_button);
	elements.add(ret);
	ret->Start();
	return ret;
}

UIelement* j1Gui::GUIAdd_VarDisplay(int x, int y, int* variable, SDL_Color color, _TTF_Font* font)
{
	iPoint pos = { x,y };
	UIelement* ret = new UIVarDisplay(pos,variable,color,font);
	elements.add(ret);
	ret->Start();
	return ret;
}

bool j1Gui::delete_element(UIelement* element)//after using me don't forget to set your UIelement* to nullptr
{
	int i = elements.find(element);
	if (i != -1) 
	{
		p2List_item<UIelement*>* elem = elements.At(i);
		LOG("deleting element %d", elem->data->type_of_element);
		RELEASE(elem->data);
		elements.del(elem);
	}
	return true;
}

bool j1Gui::UIinteraction(UIelement* element)
{
	bool ret = true;
	if (element->type_of_element == BUTTON)
	{
		UIButton* button = (UIButton*)element;
		switch (button->type)
		{
			case NEW_GAME:
			{LOG("trying to start new gmae");
			if (App->transition->StartTransition())
				App->map->change_to_next_level = true;
			break; }
			case LOAD_GAME:
			{LOG("previously on where is my plane...");
			if (App->transition->StartTransition())
				App->LoadGame();
			break; }
			case SETTINGS:
			{LOG("SETTINGS MENU OPENED");
			App->gui->GUIAdd_window(200,200, { 282,0,210,300 },"SETTINGS", true);
				break; }
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

void j1Gui::UIDebugDraw()
{
	p2List_item<UIelement*>* item = elements.start;

	while (item != NULL)
	{
		App->render->DrawQuad({ item->data->winposition.x, item->data->winposition.y, item->data->portion.w, item->data->portion.h }, 255, 0, 0, 255, false, false);
		item = item->next;
	}

}