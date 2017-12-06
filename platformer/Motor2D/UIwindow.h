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
	SDL_Texture* tex = nullptr;
	UIButton* close = nullptr;
	bool close_button = false;

public:
	UIwindow() {};
	UIwindow(iPoint pos, const char* text = "", SDL_Rect _portion = { 0,73,133,34 }, bool _close_button = false);

	~UIwindow();

	void Start();

	void Draw();

	bool OnRelease();
};

#endif 