#ifndef __UI_ELEMENT__
#define __UI_ELEMENT__

#include "p2Point.h"
#include "p2Log.h"
#include "j1Module.h"
#include "j1Gui.h"


enum UIelement_type
{
	BUTTON,
	CHECKBOX,
	IMAGE,
	TEXT,
	TEXTBOX,
	WINDOW,
	VARDISPLAY,
	NONE
};

class UIelement
{
public:
	iPoint position;
	iPoint winposition;
	SDL_Rect portion = {0,0,0,0};
	UIelement_type type_of_element = NONE;
	j1Module* callback;

	p2List<UIelement*> attached_elements;
	bool attached = false;

	bool selected = false;
	iPoint mouse_stored;
	bool active;
	bool mouseover = false;

public:
	UIelement() {};
	virtual ~UIelement() {};

	virtual void OnClick() 
	{
		if (mouseover)
		{
			active = true;
		}
	};
	virtual bool OnRelease() { 
		active = false;
		return true; };

	virtual void Draw() {};

	void Update() 
	{
		if (active && App->gui->debug)
		{
			int x;
			int y;
			App->input->GetMousePosition(x, y);
			if (attached == false)
			{
				if (mouse_stored.x != x)
					winposition.x += x - mouse_stored.x;
				if (mouse_stored.y != y)
					winposition.y += y - mouse_stored.y;
			}
			else
			{
				if (mouse_stored.x != x)
					position.x += x - mouse_stored.x;
				if (mouse_stored.y != y)
					position.y += y - mouse_stored.y;
			}
		}
		int sx;
		int sy;
		App->input->GetMousePosition(sx, sy);
		mouse_stored = { sx,sy };
	};

	void UpdateAttached()
	{
		p2List_item<UIelement*>* item = attached_elements.start;
		while (item != NULL)
		{
			item->data->winposition.x = winposition.x + item->data->position.x;
			item->data->winposition.y = winposition.y + item->data->position.y;
			item = item->next;
		}
	}

	void Attach(UIelement* element, iPoint pos)//relative to the window 
	{
		element->position = pos;//position relative to the window
		element->attached = true;
		attached_elements.add(element);
	}

	virtual bool OnActivation()
	{
		bool ret = true;
		if (callback != nullptr)
		{
			ret = callback->UIinteraction(this);
		}
		return ret;
	};

	SDL_Rect GetRect()
	{
		return {winposition.x,winposition.y,portion.w,portion.h};
	}
};

#endif 