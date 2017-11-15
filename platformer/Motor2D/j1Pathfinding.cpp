#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "j1Pathfinding.h"
#include <math.h>

j1Pathfinding::j1Pathfinding()
{
	name.create("pathfinding");
}


j1Pathfinding::~j1Pathfinding()
{}

// Called before render is available
bool j1Pathfinding::Awake(pugi::xml_node& config)
{
	LOG("Loading Pathfinding");
	bool ret = true;

	//folder.create(config.child("folder").child_value());

	ResetPath();

	return ret;
}

bool j1Pathfinding::Start()
{
	
	return true;
}

void j1Pathfinding::ResetPath()
{
	frontier.Clear();
	visited.clear();
	breadcrumbs.clear();
	//frontier.Push(iPoint(19, 4), 0);
	//visited.add(iPoint(19, 4));
	//breadcrumbs.add(iPoint(19, 4));
	memset(cost_so_far, 0, sizeof(uint) * COST_MAP * COST_MAP);
}

void j1Pathfinding::Path(int x, int y)
{
	path.Clear();
	iPoint goal = WorldToMap(x, y);

	iPoint current = goal;
	if (visited.find(goal) != -1)
	{
		path.PushBack(current);

		while (current.operator!=(visited.start->data))
		{
			current = breadcrumbs.At(visited.find(current))->data;
			path.PushBack(current);
		}
	}
}

void j1Pathfinding::PathAStar(int x, int y)
{
	path.Clear();
	iPoint goal = WorldToMap(x, y);

	path.PushBack(goal);
}

int j1Pathfinding::MovementCost(int x, int y) const
{
	int ret = -1;

	if (x >= 0 && x < data.width && y >= 0 && y < data.height)
	{
		int id = data.layers.start->next->data->Get(x, y);

		if (id == 0)
			ret = 3;
		else
			ret = 0;
	}

	return ret;
}

void j1Pathfinding::DrawPath()
{
	iPoint point;

	// Draw visited
	p2List_item<iPoint>* item = visited.start;

	while (item)
	{
		point = item->data;
		TileSet* tileset = GetTilesetFromTileId(26);

		SDL_Rect r = tileset->GetTileRect(26);
		iPoint pos = MapToWorld(point.x, point.y);

		App->render->Blit(tileset->texture, pos.x, pos.y, &r);

		item = item->next;
	}

	// Draw frontier
	for (uint i = 0; i < frontier.Count(); ++i)
	{
		point = *(frontier.Peek(i));
		TileSet* tileset = GetTilesetFromTileId(25);

		SDL_Rect r = tileset->GetTileRect(25);
		iPoint pos = MapToWorld(point.x, point.y);

		App->render->Blit(tileset->texture, pos.x, pos.y, &r);
	}

	// Draw path
	for (uint i = 0; i < path.Count(); ++i)
	{
		iPoint pos = MapToWorld(path[i].x, path[i].y);
		App->render->Blit(tile_x, pos.x, pos.y);
	}
}

bool j1Pathfinding::CleanUp()
{

}