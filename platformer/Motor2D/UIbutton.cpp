#include "UIbutton.h"
#include "j1Render.h"
#include "j1Fonts.h"
#include "j1Textures.h"

UIButton::UIButton(iPoint pos, const char* text, button_type _type, SDL_Rect _portion, bool _attached)
{
	attached = _attached;
	winposition = pos;
	type_of_element = BUTTON;
	position = { 0,0 };
	portion = _portion;
	type = _type;
	string = text;
	if (string != "")
	{
		tex = App->tex->textures.add(App->font->Print(string.GetString(), { 0,0,0,255 }, App->font->default))->data;
		SDL_QueryTexture(tex, NULL, NULL, &text_w, &text_h);
	}

	int sx;
	int sy;
	App->input->GetMousePosition(sx, sy);
	mouse_stored = { sx,sy };

}

UIButton::~UIButton()
{
	App->tex->UnLoad(tex);
};

void UIButton::Draw()
{
	if (active)
	{
		App->render->Blit(App->gui->GetAtlas(), winposition.x, winposition.y, &pressed);
	}
	else
	{
		App->render->Blit(App->gui->GetAtlas(), winposition.x, winposition.y, &portion);
	}
	if (mouseover)
	{
		App->render->Blit(App->gui->GetAtlas(), winposition.x - 15, winposition.y - 15, &glow);
		mouseover = false;
	}
	if (tex != nullptr)
		App->render->Blit(tex, winposition.x + portion.w / 2 - text_w / 2, (winposition.y + portion.h / 2 - text_h / 2) - 2);


}

void UIButton::OnClick()
{
	if (mouseover)
	{
		active = true;
	}
};

bool UIButton::OnRelease()
{
	bool ret = true;

	if (mouseover && active)
	{
		ret = OnActivation();
	}
	active = false;

	return ret;
};