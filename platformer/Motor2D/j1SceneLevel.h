#ifndef __j1SCENELEVEL_H__
#define __j1SCENELEVEL_H__

#include "j1Module.h"
#include "UIbutton.h"

struct SDL_Texture;

class j1SceneLevel : public j1Module
{
public:

	j1SceneLevel();

	// Destructor
	virtual ~j1SceneLevel();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate(float dt);

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate(float dt);

	// Called before quitting
	bool CleanUp();

	bool Save(pugi::xml_node& node) const;
	bool Load(pugi::xml_node& node);


	//pause and resume functions
	bool Pause();
	bool Resume();

	//UI interactions for the pause menu
	bool UIinteraction(UIelement* element);

	bool godmode = false;

	int score = 0;
	int lastscore = 0;
	int coins = 0;
	int lastcoins = 0;
	int lifes = 3;

	int time_left = 0;

private:

	UIButton* Continue;
	UIButton* Exit;

	SDL_Texture* pause_background;
};

#endif // __j1SCENE_H__