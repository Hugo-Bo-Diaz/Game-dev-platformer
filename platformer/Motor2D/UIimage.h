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
	bool follow_camera = false;
public:
	UIimage() {};
	UIimage(iPoint pos, SDL_Rect _rect, bool _follow_camera = false)// color is a 4 dim array in this order{r g b a} this is for the default font need to adapt it better
	{
		type_of_element = IMAGE;
		winposition = pos;
		portion = _rect;
		follow_camera = _follow_camera;
	}
	~UIimage() {};

	virtual void Draw() { 
		if (follow_camera)
			App->render->Blit(App->gui->GetAtlas(), -App->render->camera.x + winposition.x, -App->render->camera.y + winposition.y, &portion);
		else
			App->render->Blit(App->gui->GetAtlas(), winposition.x, winposition.y, &portion);

	};
};

#endif 