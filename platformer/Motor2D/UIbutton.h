#ifndef __UI_BUTTON__
#define __UI_BUTTON__

#include "p2Point.h"
#include "p2SString.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1App.h"
#include "j1Gui.h"
#include "j1Map.h"
#include "j1Render.h"
#include "UIelement.h"


class UIButton : public UIelement
{
public:
	bool clicked = false;
	SDL_Rect pressed = {144,1,133,71};
	SDL_Rect glow = {0,71,174,101};
	button_type type = NUL;
	p2SString string;
	int text_w;
	int text_h;
	SDL_Texture* tex;
public:
	UIButton() {};
	UIButton(iPoint pos,const char* text = "" , button_type _type = NUL, SDL_Rect _portion = { 0,73,133,34 })// color is a 4 dim array in this order{r g b a} this is for the default font need to adapt it better
	{

		winposition = pos;
		type_of_element = BUTTON;
		position = {0,0};
		portion = _portion;
		type = _type;
		string = text;
		if (string != "")
		{
			tex = App->tex->textures.add(App->font->Print(string.GetString(), { 0,0,0,255 }, App->font->default))->data;
			SDL_QueryTexture(tex, NULL, NULL, &text_w, &text_h);
		}
	}
	~UIButton() 
	{ 
		App->tex->UnLoad(tex);
	};

	void Draw() 
	{
		if (clicked)
		{
			App->render->Blit(App->gui->GetAtlas(), winposition.x, winposition.y, &pressed);
		}
		else
		{
			App->render->Blit(App->gui->GetAtlas(), winposition.x, winposition.y, &portion);
		}
		if (mouseover)
		{
			App->render->Blit(App->gui->GetAtlas(), winposition.x -15, winposition.y-15, &glow);
			mouseover = false;
		}
		if (tex != nullptr)
			App->render->Blit(tex, winposition.x + portion.w / 2 - text_w / 2, (winposition.y + portion.h / 2 - text_h / 2) -2);
	};

	void OnClick() { clicked = true; };
	void OnMouseOver() { mouseover = true; };
	bool OnRelease() 
	{
		bool ret = true;

		if (mouseover && clicked) 
		{ 
			ret = OnActivation();
		} 
		clicked = false;
		return ret;
	};

	//functions for the buttons
};

#endif 