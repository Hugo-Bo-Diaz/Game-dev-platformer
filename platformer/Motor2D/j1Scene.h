#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"
#include "UIbutton.h"
#include "UItextbox.h"
struct SDL_Texture;

struct HighScore 
{
	p2SString name;
	int score;
};


class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

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

	int final_score = 0;

	int time_left = 0;

	p2List<HighScore*> highscores;
	UITextbox* name_highscore;

private:

	UIwindow* Pause_window;
	UIButton* Continue;
	UIButton* Settings;
	UIButton* Exit;

	UIwindow* Settings_window;

	SDL_Texture* pause_background;
};

#endif // __j1SCENE_H__