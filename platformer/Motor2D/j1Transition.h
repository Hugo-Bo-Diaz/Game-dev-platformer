#ifndef __j1TRANSITION_H__
#define __j1TRANSITION_H__

#include "j1Module.h"
#include "SDL\include\SDL_pixels.h"
#include "p2Point.h"

struct SDL_Texture;

class j1Transition : public j1Module
{
public:

	j1Transition();

	// Destructor
	virtual ~j1Transition();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called to update the transition
	bool PostUpdate(float dt);

	// Called to start a transition
	void StartTransition();

	// Called before quitting
	bool CleanUp();

public:

	bool transitioning = false;
	SDL_Texture* transition;

private:

	int width = 750;
	int height = 420;
	iPoint pos = {0,0};
	int speed = 30;
};


#endif // __j1FONTS_H__