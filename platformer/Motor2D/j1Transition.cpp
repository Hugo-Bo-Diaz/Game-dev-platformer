#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Transition.h"
#include "j1Render.h"

j1Transition::j1Transition() : j1Module()
{
	name.create("transition");
	active_in_pause = false;
}

// Destructor
j1Transition::~j1Transition()
{}

// Called before render is available
bool j1Transition::Awake(pugi::xml_node& conf)
{
	bool ret = true;
	speed = conf.child("speed").attribute("value").as_int(60);
	return ret;
}

// Called before quitting
bool j1Transition::CleanUp()
{
	App->tex->UnLoad(transition);
	return true;
}

// Update position of the transition
bool j1Transition::PostUpdate(float dt)
{
	bool ret = true;

	float thousanddivdt = 1000 / dt;// ~ frame RATE

	float normalize_factor = 60 / thousanddivdt;//60 is the ideal framerate for the given speeds	

	if (normalize_factor < 1) { normalize_factor = 1; }
	switch (trans)
		case 1:
		{
		App->render->Blit(transition, pos.x, pos.y);
		if (pos.x > -width)
		{
			pos.x -= speed*normalize_factor;//NEEDS NORMALIZATION
		}
		else
		{
			transitioning = false;
			trans = 0;
			App->tex->UnLoad(transition);
		}
		break;
		default:
			break;
		}

	return ret;
}

// calculate size of a text
bool j1Transition::StartTransition()
{
	if (!transitioning)
	{
		SDL_Surface *sshot = SDL_CreateRGBSurface(0, 750, 420, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
		SDL_RenderReadPixels(App->render->renderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
		transition = App->tex->LoadSurface(sshot);
		SDL_FreeSurface(sshot);
		sshot = nullptr;
		transitioning = true;
		pos.x = 0;
		return true;
	}
	else
	{
		LOG("transition already in progress, try again when it finishes");
		return false;
	}

	trans = 1;
}

bool j1Transition::FadeBlack(float time)
{
	fade_timer = time;
	timer_to_black.Start();
	trans = 2;

	return true;
}