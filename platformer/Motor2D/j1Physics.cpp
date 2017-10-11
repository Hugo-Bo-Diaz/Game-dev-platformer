#include "j1Physics.h"
#include "j1Collision.h"
#include "j1App.h"
#include "p2Log.h"

j1Physics::j1Physics()
{

}

bool j1Physics::Awake(pugi::xml_node* config)
{
	/*objects = new object[MAX_OBJECTS];

	memset(objects, 0, sizeof(object)*(MAX_OBJECTS));*/

	return true;
}

object* j1Physics::Addobject(int _x, int _y, int _gravity, SDL_Rect* collision,COLLIDER_TYPE TYPE, j1Module* Callback)
{
	object* ret = nullptr;

	for (uint i = 0; i < MAX_OBJECTS; ++i)//15 = MAX OBJECTS THAT SHOULD BE IN THE CONFIG FILE
	{
		if (objects[i] == nullptr)
		{
			ret = objects[i] = new object;
			break;
		}
	}

	ret->position.x = _x;
	ret->position.y = _y;
	ret->gravity = _gravity;
	
	ret->col = App->collision->AddCollider(*collision, TYPE, Callback);
	ret->predictor = App->collision->AddCollider(*collision, COLLIDER_FUTURE, this);

	ret->velocity.x = 0;
	ret->velocity.y = 0;

	return ret;

}

bool j1Physics::CleanUp()
{
	LOG("Freeing all objects");

	for (uint i = 0; i < MAX_OBJECTS; ++i)
	{
		if (&objects[i] != nullptr)
		{
			delete &objects[i];
			//objects[i] = nullptr;
		}
	}

	return true;
}

bool j1Physics::PreUpdate()
{
//HERE U SET THE RECTANGLE FUTURE FOR THE ITEMS SO THEY COLLIDE WHEN THE TIME COMES AND YOU GET THE FUNCTION CALLED
	for (uint i = 0; i < MAX_OBJECTS; ++i)
	{
		if (objects[i] != nullptr)
		objects[i]->predictor->SetPos(	objects[i]->position.x + objects[i]->velocity.x,
										objects[i]->position.y + objects[i]->velocity.y);
	}
	return true;
}

void j1Physics::OnCollision(Collider* c1,Collider*c2)
{
	//this means this is going to collide next frame
	if (c1->type == COLLIDER_FUTURE)
	{
		SDL_Rect result;
		SDL_bool _bool = SDL_IntersectRect(&c1->rect,&c2->rect, &result);
		if (_bool)//this means they collided 4 real
		{
			/*for (uint i = 0; i < MAX_OBJECTS; ++i)
			{
				if (objects[i]->predictor->rect.x == c1->rect.x&&
					objects[i]->predictor->rect.y == c1->rect.y&&
					objects[i]->predictor->rect.w == c1->rect.w&&
					objects[i]->predictor->rect.h == c1->rect.h)
				{*/
				object* obj= GetObjectFromRect_predictor(&result);
					if (result.h >= result.w)
					{
						obj->position.x = obj->predictor->rect.x - result.w;
					}
					else
					{
						obj->position.y = obj->predictor->rect.y - result.h;
					}
				//}
			//}


		}
	}
};

object* j1Physics::GetObjectFromRect_predictor(SDL_Rect* rectangle)
{
	for (uint i = 0; i < MAX_OBJECTS; ++i)
	{
		if (objects[i]->predictor->rect.x == rectangle->x&&
			objects[i]->predictor->rect.y == rectangle->y&&
			objects[i]->predictor->rect.w == rectangle->w&&
			objects[i]->predictor->rect.h == rectangle->h)
		{
			return objects[i];
		}
	}
}