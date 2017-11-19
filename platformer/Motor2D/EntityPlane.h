#ifndef _J1PLANE_H_
#define _J1PLANE_H_

#include "j1Physics.h"
#include "EntityBackground.h"

class EntityPlane : public EntityBackground
{
public:

	EntityPlane();
	~EntityPlane()
	{};

	void Draw();
	void Start();

	void CleanUp();

};


#endif // !
