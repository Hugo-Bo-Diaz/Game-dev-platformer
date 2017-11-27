#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "UIelement.h"
#include "j1Fonts.h"


#define CURSOR_WIDTH 2

// TODO 1: Create your structure of classes

// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate(float dt);

	// Called after all Updates
	bool PostUpdate(float dt);

	// Called before quitting
	bool CleanUp();

	// TODO 2: Create the factory methods
	// Gui creation functions

	SDL_Texture* GetAtlas() const;
	

	UIelement* GUIAdd_text(int x, int y, const char* text, SDL_Color color = {175,175,175,255}, _TTF_Font* font = App->font->default);
	UIelement* GUIAdd_image(int x, int y, SDL_Rect portion);
	UIelement* GUIAdd_button(int x, int y, SDL_Rect portion, const char* text, button_type type = button_type::NUL);
	UIelement* GUIAdd_checkbox(int x, int y, SDL_Rect portion, const char* text);
	UIelement* GUIAdd_textbox(int x, int y, const char* title = "");

	//portion in this functions means the part of the atlas they get to draw

private:

	SDL_Texture* atlas;
	p2SString atlas_file_name;

	p2List<UIelement*> elements;

	bool MouseInside(SDL_Rect* rect);
};

#endif // __j1GUI_H__