#ifndef __UI_VARDISPLAY__
#define __UI_VARDISPLAY__

#include "p2SString.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1App.h"
#include "UIelement.h"
#include "j1Gui.h"
#include "j1Render.h"
#include <stdlib.h>

class UIVarDisplay : public UIelement
{
public:
	SDL_Texture* texture;
	float* variable;
	SDL_Color color;
public:
	UIVarDisplay() {};
	UIVarDisplay(iPoint pos,float* _variable,  SDL_Color _color, _TTF_Font* font = App->font->default)// color is a 4 dim array in this order{r g b a} this is for the default font need to adapt it better
	{
		winposition = pos;
		color = _color;
		variable = _variable;
		type_of_element = VARDISPLAY;

	}
	~UIVarDisplay() { };

	virtual void Draw() 
	{ 
		if (variable != nullptr)
		{
			int value = *variable;
			std::string s = std::to_string(value);
			p2SString pchar = s.c_str();
			SDL_Texture* tex = App->font->Print(pchar.GetString(), color, App->font->fonts.start->data);
			App->render->Blit(tex, winposition.x, winposition.y);
			SDL_DestroyTexture(tex);
		}
	};
};

#endif 