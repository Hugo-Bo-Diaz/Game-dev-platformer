#ifndef __UI_SLIDER__
#define __UI_SLIDER__

#include "p2SString.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1App.h"
#include "UIelement.h"


class UIslider : public UIelement
{
public:
	SDL_Texture* title_text;
	int* variable;
	SDL_Color color;
	SDL_Rect start;
	SDL_Rect end;
	SDL_Rect middle;
	SDL_Rect button;
	iPoint mouse_stored;
	int position_x;
	int movement_x;
	float max_value;
	p2SString title_string;

public:
	UIslider() {};
	UIslider(iPoint pos, int* _variable,SDL_Rect portion,SDL_Rect start,SDL_Rect end, SDL_Rect middle,SDL_Rect button, int _max_value, const char* title = "");
	~UIslider();

	void Start();

	void OnClick();

	bool OnRelease();

	void Draw();
};

#endif 