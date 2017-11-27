#ifndef __UI_IMAGE__
#define __UI_IMAGE__

#include "p2Point.h"
#include "p2SString.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1App.h"
#include "UIelement.h"
#include "j1Gui.h"
#include "j1Render.h"

class UIimage : public UIelement
{
public:

public:
	UIimage() {};
	UIimage(iPoint pos,SDL_Rect _rect)// color is a 4 dim array in this order{r g b a} this is for the default font need to adapt it better
	{
		position = pos;
		portion = _rect;
	}
	~UIimage() {};

	virtual void Draw() { 
		App->render->Blit(App->gui->GetAtlas(),position.x,position.y,&portion); 
	};
};

#endif 