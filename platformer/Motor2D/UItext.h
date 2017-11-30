#ifndef __UI_TEXT__
#define __UI_TEXT__

#include "p2SString.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1App.h"
#include "UIelement.h"
#include "j1Gui.h"
#include "j1Render.h"

class UItext : public UIelement
{
public:
	SDL_Texture* texture;
	p2SString text;
	SDL_Color color;
public:
	UItext() {};
	UItext(iPoint pos, const char* _text, SDL_Color _color, _TTF_Font* font = App->font->default)// color is a 4 dim array in this order{r g b a} this is for the default font need to adapt it better
	{
		winposition = pos;
		//text.create(_text);
		texture = App->tex->textures.add(App->font->Print(_text,_color,font))->data;
		//color = _color;
		type_of_element = TEXT;

	}
	~UItext() { App->tex->UnLoad(texture); };

	virtual void Draw() 
	{ 
		App->render->Blit(texture, winposition.x, winposition.y);
	};
};

#endif 