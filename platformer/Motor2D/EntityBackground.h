#ifndef _J1BACKGROUND_H_
#define _J1BACKGROUND_H_

#include "j1Physics.h"
#include "Entity.h"

class EntityBackground : public Entity
{
public:

	EntityBackground();
	~EntityBackground()
	{
	
	};

	void Draw();
	bool Update(float dt);
	void Start();

	void CleanUp();

};


#endif // !
