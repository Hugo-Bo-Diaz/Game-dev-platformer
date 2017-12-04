#include "UIwindow.h"
#include "j1Input.h"
#include "j1Fonts.h"
#include "j1App.h"
#include "j1Render.h"

UIwindow::UIwindow(iPoint pos, const char* text, SDL_Rect _portion)// color is a 4 dim array in this order{r g b a} this is for the default font need to adapt it better
{
	type_of_element = WINDOW;
	winposition = pos;
	portion = _portion;
	title = text;
	if (title != "")
	{
		tex = App->tex->textures.add(App->font->Print(title.GetString(), { 0,0,0,255 }, App->font->default))->data;
		SDL_QueryTexture(tex, NULL, NULL, &text_w, &text_h);
	}
}

UIwindow::~UIwindow()
{
	App->tex->UnLoad(tex);
}

void UIwindow::Draw()
{
	App->render->Blit(App->gui->GetAtlas(), winposition.x, winposition.y, &portion);
	if (mouseover)
	{
		mouseover = false;
	}
	if (tex != nullptr)
		App->render->Blit(tex, winposition.x + portion.w / 2 - text_w / 2, winposition.y + 10);
}

bool UIwindow::OnRelease()
{
	bool ret = true;

	active = false;

	return ret;
};