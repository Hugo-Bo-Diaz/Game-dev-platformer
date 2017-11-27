#ifndef __UI_TEXTBOX__
#define __UI_TEXTBOX__

#include "p2Point.h"
#include "p2SString.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1App.h"
#include "j1Gui.h"
#include "j1Render.h"
#include "j1Input.h"
#include "UIelement.h"

class UITextbox : public UIelement
{
public:
	bool mouseover = false;
	bool clicked = false;
	p2SString string;
	int title_w;
	int title_h;
	int text_w;	
	int text_h;
	SDL_Texture* tex;
	bool active = false;

	p2SString text;
public:
	UITextbox() {};
	UITextbox(iPoint pos,const char* name)// color is a 4 dim array in this order{r g b a} this is for the default font need to adapt it better
	{
		position = pos;
		string = name;
		tex = App->tex->textures.add(App->font->Print(string.GetString(), { 255,255,0,255 }, App->font->default))->data;
		SDL_QueryTexture(tex, NULL, NULL, &title_w, &title_h);
		portion = { 123,0,126,22 };
	}
	~UITextbox() { App->tex->UnLoad(tex); };

	void Draw() {
		//text box
		App->render->Blit(App->gui->GetAtlas(), position.x, position.y, &portion);

		if (App->input->GetMouseButtonDown(1) == KEY_UP && !mouseover)
		{
			active = false;
		}

		//update text from the input buffer
		if (active && text.Length() < 20)//max chars
		{
			text += App->input->buffered_text;
			App->input->buffered_text.Clear();
		}
		if (App->input->GetKey(SDL_SCANCODE_BACKSPACE) == KEY_DOWN && text.Length() >0 && active)
		{
			text.CutLast();
		}
		
		//text
		if (text.Length() > 0)
		{
			SDL_Texture* text_texture = App->tex->textures.add(App->font->Print(text.GetString(), { 255,255,0,255 }, App->font->default))->data;
			
			SDL_QueryTexture(text_texture, NULL, NULL, &text_w, &text_h);

			App->render->Blit(text_texture, position.x + portion.w / 2 - text_w / 2, position.y);
			App->tex->UnLoad(text_texture);
		}
		//title
		App->render->Blit(tex, position.x + portion.w / 2 - title_w / 2, (position.y + portion.h / 2 - title_h / 2) -22);
	

		mouseover = false;
	};

	void OnClick() 
	{
		active = true;
		App->input->StartKeyInput();
		clicked = false;
	};
	void OnMouseOver()
	{
		mouseover = true;
	}
	bool OnRelease() 
	{
		bool ret = true;
		return ret;
	};

	//functions for the buttons
};

#endif 