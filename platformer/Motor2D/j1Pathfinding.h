#ifndef __j1PATHFINDING_H__
#define __j1PATHFINDING_H__

#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"
#include "SDL/include/SDL.h"
#include "p2PQueue.h"
#include "p2DynArray.h"
#include "j1Module.h"

#define COST_MAP 100

class j1Pathfinding : public j1Module
{
public:
	j1Pathfinding();

	~j1Pathfinding();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);
	bool Start();

	// Called each loop iteration
	void Draw();

	// Called before quitting
	bool CleanUp();

	// Load new map
	bool Load(const char* path);

	iPoint MapToWorld(int x, int y) const;
	iPoint WorldToMap(int x, int y) const;

	// Pathfinding
	int MovementCost(int x, int y) const;
	void ResetPath();
	void DrawPath();
	void Path(int x, int y);
	void PathAStar(int x, int y);

	void PropagateAStar();

private:

	p2PQueue<iPoint>	frontier;
	p2List<iPoint>		visited;
	p2List<iPoint>		breadcrumbs;
	uint				cost_so_far[COST_MAP][COST_MAP];
	p2DynArray<iPoint>	path;
	SDL_Texture*		tile_x = nullptr;
	iPoint				A_Star_Goal;
};

#endif