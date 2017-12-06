#include "UISlider.h"
#include "j1Gui.h"
#include "j1Render.h"

UIslider::UIslider(iPoint pos, int* _variable, SDL_Rect _portion, SDL_Rect _start, SDL_Rect _end, SDL_Rect _middle, SDL_Rect _button)// color is a 4 dim array in this order{r g b a} this is for the default font need to adapt it better
{
	winposition = pos;
	variable = _variable;
	type_of_element = SLIDER;
	portion = _portion;
	start = _start;
	end = _end;
	middle = _middle;
	button = _button;
}

void UIslider::Draw()
{

	//blit middle
	int number_of_middle_pieces = (portion.w-start.w) / middle.w;
	for (int i = 0; i < number_of_middle_pieces; ++i)
	{
		int position_y = winposition.y + (portion.h / 2 - middle.h / 2);
		App->render->Blit(App->gui->GetAtlas(), winposition.x +start.w + (middle.w*i), position_y, &middle);
	}

	//blit start
	App->render->Blit(App->gui->GetAtlas(),winposition.x,winposition.y,&start);
	
	//blit end
	App->render->Blit(App->gui->GetAtlas(),winposition.x + (portion.w - end.w),winposition.y, &end);
	

	//blit and calculate variable piece
	//first we need to know where to draw it we need its position in % we need a max value(i'll asume 0 is min)
	float max_value = 128;//trying to do this to the volume, will adapt later

	float value = *variable;
	float percent = (value / max_value);
	//now we need it to draw it accordingly

	int movement_x = portion.w - start.w - end.w - button.w;//all the moves are here
	int position_x = winposition.x + start.w + movement_x*percent;// here its his position
	App->render->Blit(App->gui->GetAtlas(), position_x , winposition.y, &button);


	if (mouseover)
	{
		mouseover = false;
	}
};