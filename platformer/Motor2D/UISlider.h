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
	SDL_Texture* texture;
	int* variable;
	SDL_Color color;
	SDL_Rect start;
	SDL_Rect end;
	SDL_Rect middle;
	SDL_Rect button;

public:
	UIslider() {};
	UIslider(iPoint pos, int* _variable,SDL_Rect portion,SDL_Rect start,SDL_Rect end, SDL_Rect middle,SDL_Rect button);
	~UIslider() {};

	void Draw();
};

#endif 