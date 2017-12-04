#ifndef __UI_BUTTON__
#define __UI_BUTTON__

#include "p2Point.h"
#include "p2SString.h"
#include "j1App.h"
#include "j1Input.h"
#include "UIelement.h"

struct SDL_Texture;

class UIButton : public UIelement
{
public:
	SDL_Rect pressed = {144,1,133,71};
	SDL_Rect glow = {0,71,174,101};
	button_type type = NUL;
	p2SString string;
	int text_w;
	int text_h;
	SDL_Texture* tex;

public:
	UIButton() {};
	UIButton(iPoint pos, const char* text = "", button_type _type = NUL, SDL_Rect _portion = { 0,73,133,34 });// color is a 4 dim array in this order{r g b a} this is for the default font need to adapt it better
	~UIButton();

	void Draw();
	void OnClick();
	bool OnRelease();


	//functions for the buttons
};

#endif 