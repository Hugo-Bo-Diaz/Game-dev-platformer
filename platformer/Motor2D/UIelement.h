#ifndef __UI_ELEMENT__
#define __UI_ELEMENT__

#include "p2Point.h"
#include "p2Log.h"
#include "j1Module.h"

enum button_type
{
	NEW_GAME,
	LOAD_GAME,
	CREDITS,
	SETTINGS,
	QUIT,
	NUL
};

enum UIelement_type
{
	BUTTON,
	CHECKBOX,
	IMAGE,
	TEXT,
	TEXTBOX,
	NONE
};

class UIelement
{
public:
	iPoint position;
	SDL_Rect portion = {0,0,0,0};
	UIelement_type type_of_element = NONE;
	j1Module* callback;
	bool mouseover = false;
public:
	UIelement() {};
	~UIelement() {};

	virtual void OnClick() {};
	virtual bool OnRelease() { return true; };

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

	SDL_Rect GetRect()
	{
		return {position.x,position.y,portion.w,portion.h};
	}
};

#endif 