#ifndef __UI_TEXTBOX__
#define __UI_TEXTBOX__

#include "p2Point.h"
#include "p2SString.h"
#include "UIelement.h"

class UITextbox : public UIelement
{
public:
	p2SString string;
	int title_w;
	int title_h;
	int text_w;	
	int text_h;
	SDL_Texture* tex;
	SDL_Texture* default_text;

	p2SString text;
	bool texting = false;
	int text_pos=0;

public:
	UITextbox() {};
	UITextbox(iPoint pos, const char* name, const char* default_text);
	~UITextbox();


	void Draw(); 

	void OnClick();

	bool OnRelease();

	//functions for the buttons
};

#endif 