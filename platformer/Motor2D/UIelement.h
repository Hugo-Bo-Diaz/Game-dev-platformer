#ifndef __UI_ELEMENT__
#define __UI_ELEMENT__

#include "p2Point.h"
#include "p2Log.h"
#include "j1Module.h"
#include "j1Gui.h"
#include "j1Input.h"


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

	virtual void Start() {};

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

	virtual bool OnActivation()
	{
		bool ret = true;
		if (callback != nullptr)
		{
			ret = callback->UIinteraction(this);
		}
		return ret;
	};

	void Update();

	void UpdateAttached();

	void Attach(UIelement* element, iPoint pos);//relative to the window 


	SDL_Rect GetRect()
	{
		return {winposition.x,winposition.y,portion.w,portion.h};
	}
};

#endif 