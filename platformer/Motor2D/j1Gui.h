#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "UIelement.h"
#include "j1Fonts.h"

#define CURSOR_WIDTH 2

// TODO 1: Create your structure of classes

class UIwindow;
class UIButton;
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
	
	bool UIinteraction(UIelement* element);


	UIelement* GUIAdd_text(int x, int y, const char* text, j1Module* callback = nullptr, SDL_Color color = {175,175,175,255}, _TTF_Font* font = App->font->default);
	UIelement* GUIAdd_image(int x, int y, SDL_Rect portion, j1Module* callback = nullptr);
	UIelement* GUIAdd_button(int x, int y, SDL_Rect portion, j1Module* callback = nullptr, const char* text = "", button_type type = button_type::NUL);
	UIelement* GUIAdd_checkbox(int x, int y, SDL_Rect portion, j1Module* callback = nullptr, const char* text = "");
	UIelement* GUIAdd_textbox(int x, int y, j1Module* callback = nullptr, const char* title = "");
	UIelement* GUIAdd_window(int x, int y, SDL_Rect portion, const char* title, bool dragable);
	//portion in this functions means the part of the atlas they get to draw

	bool delete_element(UIelement* element);

	UIwindow* window_ui;
	UIButton* button_test;

private:

	SDL_Texture* atlas;
	p2SString atlas_file_name;

	p2List<UIelement*> elements;

	bool MouseInside(SDL_Rect* rect);
	SDL_Texture* screen = nullptr;
};

#endif // __j1GUI_H__