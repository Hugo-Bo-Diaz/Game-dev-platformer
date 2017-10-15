#include "j1Physics.h"
#include "j1Collision.h"
#include "j1App.h"
#include "p2Log.h"

j1Physics::j1Physics()
{	
	//here we initialise all object to nullptr
	for (uint i = 0; i < MAX_OBJECTS; ++i)
		objects[i] = nullptr;
}

bool j1Physics::Awake(pugi::xml_node* config)
{
	/*objects = new object[MAX_OBJECTS];

	memset(objects, 0, sizeof(object)*(MAX_OBJECTS));*/

	return true;
}

object* j1Physics::Addobject(float _x, float _y, float _gravity, SDL_Rect* collision,COLLIDER_TYPE TYPE, j1Module* Callback)
{
	object* ret = nullptr;
	//looks free object slot
	for (uint i = 0; i < MAX_OBJECTS; ++i)
	{
		if (objects[i] == nullptr)
		{
			ret = objects[i] = new object;
			break;
		}
	}
	//assign all the object properties
	ret->position.x = _x;
	ret->position.y = _y;
	ret->acceleration.x = 0;
	ret->acceleration.y = _gravity;


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
		if (objects[i] != nullptr)
		{
			if (objects[i]->col != nullptr)
				objects[i]->col->to_delete = true;
			if (objects[i]->predictor != nullptr)
				objects[i]->predictor->to_delete = true;
			delete objects[i];
			//objects[i] = nullptr;
		}
	}

	return true;
}

bool j1Physics::PreUpdate()
{
//we set up the colliders that will check the collisions in the near future
	for (uint i = 0; i < MAX_OBJECTS; ++i)
	{
		if (objects[i] != nullptr)
		{
			float change_x = objects[i]->velocity.x +objects[i]->acceleration.y;
			float change_y = objects[i]->velocity.y +objects[i]->acceleration.y;
			objects[i]->predictor->SetPos(objects[i]->position.x + change_x,
										objects[i]->position.y + change_y);
		}
	}
	return true;
}

bool j1Physics::Update(float dt)
{
	//advance objects
	for (uint i = 0; i < MAX_OBJECTS; ++i)
	{
		if (objects[i] != nullptr)
		{
			objects[i]->velocity += objects[i]->acceleration;

			objects[i]->position += objects[i]->velocity;
		}
	}
	return true;
}

void j1Physics::OnCollision(Collider* c1,Collider*c2)
{
	//this method wil be called on an earlier update method(module collisions)
	if (c1->type == COLLIDER_FUTURE)
	{
		SDL_Rect result;//this is the rectangle that they share when they are colliding
						//from here we know how much they are colliding and know how much to push back these collisions
		SDL_bool _bool = SDL_IntersectRect(&c1->rect,&c2->rect, &result);
		if (_bool)//this means they collided 4 real
		{
			//logic operations
			object* obj= GetObjectFromRect_predictor(&c1->rect);
			if (result.h > result.w)
			{
				if (c1->rect.x <c2->rect.x)
				{obj->position.x = obj->predictor->rect.x - result.w-3;}
				else
				{obj->position.x = obj->predictor->rect.x + result.w+3;}
				obj->velocity.x = 0;
			}
			else if (result.h <= result.w)
			{
				if (c1->rect.y < c2->rect.y)
				{obj->position.y = obj->predictor->rect.y - result.h;
				obj->grounded = true;}
				else
				{obj->position.y = obj->predictor->rect.y + result.h;}
				obj->velocity.y = 0;
			}
		}
	}
};

bool j1Physics::PostUpdate() 
{
	// here is where the colliders positions are adjusted to where they should be
	for (uint i = 0; i < MAX_OBJECTS; ++i)
	{
		if (objects[i] != nullptr)
		{
			objects[i]->col->SetPos(objects[i]->position.x, objects[i]->position.y);
		}
	}
	return true;
}

//this is to know whose collider was called from the OnCollision method
object* j1Physics::GetObjectFromRect_predictor(SDL_Rect* rectangle)
{
	for (uint i = 0; i < MAX_OBJECTS; ++i)
	{
		if (objects[i] != nullptr)
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
}