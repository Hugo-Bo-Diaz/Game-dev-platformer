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

	// Pathfinding
	bool IsWalkable(int x, int y) const;
	void ResetPath(p2DynArray<iPoint>& path_);
	//void DrawPath();
	void Path(iPoint goal_, p2DynArray<iPoint>& path_);

	bool PropagateAStar(p2DynArray<iPoint>& path_, Entity* entity_, Entity* target_);

private:

	p2PQueue<iPoint>	frontier;
	p2List<iPoint>		visited;
	p2List<iPoint>		breadcrumbs;
	uint				cost_so_far[COST_MAP][COST_MAP];
};

#endif