#ifndef __UI_WINDOW__
#define __UI_WINDOW__

#include "p2SString.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1App.h"
#include "j1Render.h"
#include "UIelement.h"
#include "j1Input.h"

class UIwindow : public UIelement
{
public:
	p2SString title;
	int text_w;
	int text_h;
	SDL_Texture* tex;

public:
	UIwindow() {};
	UIwindow(iPoint pos,const char* text = "" , SDL_Rect _portion = { 0,73,133,34 })// color is a 4 dim array in this order{r g b a} this is for the default font need to adapt it better
	{
		type_of_element = WINDOW;
		winposition = pos;
		portion = _portion;
		title = text;
		if (title != "")
		{
			tex = App->tex->textures.add(App->font->Print(title.GetString(), { 0,0,0,255 }, App->font->default))->data;
			SDL_QueryTexture(tex, NULL, NULL, &text_w, &text_h);
		}
	}
	~UIwindow()
	{ 
		App->tex->UnLoad(tex);
	};

	void Draw() 
	{		

		App->render->Blit(App->gui->GetAtlas(), winposition.x, winposition.y, &portion);
		if (mouseover)
		{
			mouseover = false;
		}
		if (tex != nullptr)
			App->render->Blit(tex, winposition.x + portion.w / 2 - text_w / 2, winposition.y+ 10);


	};

	void Update()
	{
		if (active && App->gui->debug)
		{
			int x;
			int y;
			App->input->GetMousePosition(x, y);
			if (mouse_stored.x != x)
				winposition.x += x - mouse_stored.x;
			if (mouse_stored.y != y)
				winposition.y += y - mouse_stored.y;
		}
		int sx;
		int sy;
		App->input->GetMousePosition(sx, sy);
		mouse_stored = { sx,sy };

	}

	void OnClick() 
	{
		if (mouseover)
		{
			active = true;
		}
	};
	void OnMouseOver() { mouseover = true; };
	bool OnRelease() 
	{
		bool ret = true;

		active = false;

		return ret;
	};

	//functions for the buttons
};

#endif 