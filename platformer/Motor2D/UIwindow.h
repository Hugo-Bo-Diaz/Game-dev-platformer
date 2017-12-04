#ifndef __UI_WINDOW__
#define __UI_WINDOW__

#include "p2SString.h"
#include "j1Textures.h"
#include "UIelement.h"

class UIwindow : public UIelement
{
public:
	p2SString title;
	int text_w;
	int text_h;
	SDL_Texture* tex;

public:
	UIwindow() {};
	UIwindow(iPoint pos, const char* text = "", SDL_Rect _portion = { 0,73,133,34 });

	~UIwindow();

	void Draw();

	bool OnRelease();
};

#endif 