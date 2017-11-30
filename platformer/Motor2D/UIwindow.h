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
	bool clicked = false;
	p2SString title;
	int text_w;
	int text_h;
	SDL_Texture* tex;
	iPoint mouse_stored;
	p2List<UIelement*> contents;
	bool active = false;
	bool dragable=false;
public:
	UIwindow() {};
	UIwindow(iPoint pos,const char* text = "" , SDL_Rect _portion = { 0,73,133,34 }, bool _dragable = false)// color is a 4 dim array in this order{r g b a} this is for the default font need to adapt it better
	{
		type_of_element = WINDOW;
		winposition = pos;
		portion = _portion;
		title = text;
		dragable = _dragable;
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
		if (active && dragable)
		{
			int x;
			int y; 
			App->input->GetMousePosition(x, y);
			if (mouse_stored.x != x)
				winposition.x += x-mouse_stored.x;
			if (mouse_stored.y != y)
				winposition.y += y-mouse_stored.y;
		}
		App->render->Blit(App->gui->GetAtlas(), winposition.x, winposition.y, &portion);
		if (mouseover)
		{
			mouseover = false;
		}
		if (tex != nullptr)
			App->render->Blit(tex, winposition.x + portion.w / 2 - text_w / 2, winposition.y+ 10);

		p2List_item<UIelement*>* item = contents.start;
		while (item != NULL)
		{
			item->data->winposition.x = winposition.x + item->data->position.x;
			item->data->winposition.y = winposition.y + item->data->position.y;
			item = item->next;
		}
		int sx;
		int sy;
		App->input->GetMousePosition(sx, sy);
		mouse_stored = { sx,sy };
	};

	void Attach(UIelement* element, iPoint pos)//relative to the window 
	{ 
		element->position = pos;//position relative to the window
		contents.add(element);
	}

	void OnClick() 
	{
		active = true;
		clicked = true;
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