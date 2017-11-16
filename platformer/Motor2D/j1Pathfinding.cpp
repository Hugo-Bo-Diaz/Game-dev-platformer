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

void j1Pathfinding::ResetPath(p2DynArray<iPoint>& path_)
{
	frontier.Clear();
	visited.clear();
	breadcrumbs.clear();
	path_.Clear();

	memset(cost_so_far, 0, sizeof(uint) * COST_MAP * COST_MAP);
}

bool j1Pathfinding::IsWalkable(int x, int y) const
{
	bool ret = false;
	int id = 1;
	if (x >= 0 && x < App->map->data.width && y >= 0)
	{
		p2List_item<map_layer*>* item = App->map->data.layers.start;
		while (item != NULL)
		{
			if (item->data->logic_layer)
			{
				int id = item->data->Get(x, y);
			}
			item = item->next;
		}
		if (id == 0)
			ret = true;
	}

	return ret;
}

bool j1Pathfinding::PropagateAStar(p2DynArray<iPoint>& path_, Entity* entity_, Entity* target_)
{
	bool ret = false;

	ResetPath(path_);

	iPoint goal = App->map->WorldToMap(target_->position.x, target_->position.y);
	iPoint origin = App->map->WorldToMap(entity_->position.x, entity_->position.y);

	frontier.Push(origin, 0);
	visited.add(origin);
	breadcrumbs.add(origin);

	while (visited.find(goal) == -1)
	{
		iPoint curr;
		uint new_cost;

		if (frontier.Pop(curr))
		{
			iPoint neighbors[4];
			neighbors[0].create(curr.x + 1, curr.y + 0);
			neighbors[1].create(curr.x + 0, curr.y + 1);
			neighbors[2].create(curr.x - 1, curr.y + 0);
			neighbors[3].create(curr.x + 0, curr.y - 1);

			for (uint i = 0; i < 4; ++i)
			{
				int distance = neighbors[i].DistanceNoSqrt(goal);

				if (IsWalkable(neighbors[i].x, neighbors[i].y))
				{
					new_cost = cost_so_far[curr.x][curr.y] + 1;

					if (cost_so_far[neighbors[i].x][neighbors[i].y] == 0 || new_cost < cost_so_far[neighbors[i].x][neighbors[i].y])
					{
						cost_so_far[neighbors[i].x][neighbors[i].y] = new_cost;

						if (visited.find(neighbors[i]) == -1)
						{
							if (neighbors[i] != goal)
								frontier.Push(neighbors[i], new_cost + distance * 10);

							visited.add(neighbors[i]);
							breadcrumbs.add(curr);
						}
						else
							breadcrumbs.At(visited.find(neighbors[i]))->data = curr;
					}
				}
			}
		}
		ret = true;
	}

	Path(goal, path_);

	return ret;
}

void j1Pathfinding::Path(iPoint goal_, p2DynArray<iPoint>& path_)
{
	iPoint current = goal_; // breadcrumbs.At(visited.find(goal))->data;

	if (visited.find(goal_) != -1)
	{
		path_.PushBack(current);

		while (current != visited.start->data)
		{
			current = breadcrumbs.At(visited.find(current))->data;
			path_.PushBack(current);
		}
		path_.Flip();
	}
}
