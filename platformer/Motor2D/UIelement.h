#ifndef __UI_ELEMENT__
#define __UI_ELEMENT__

#include "p2Point.h"
#include "p2Log.h"

enum button_type
{
	NEW_GAME,
	LOAD_GAME,
	CREDITS,
	QUIT,
	NUL
};

class UIelement
{
public:
	iPoint position;
	SDL_Rect portion = {0,0,0,0};
public:
	UIelement() {};
	~UIelement() {};

	virtual void OnClick() {};
	virtual bool OnRelease() { return true; };
	virtual void OnMouseOver() {  };

	virtual void Draw() {};

	SDL_Rect GetRect()
	{
		return {position.x,position.y,portion.w,portion.h};
	}
};

#endif 