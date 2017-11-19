#ifndef _J1THANKSFORPLAYING_H_
#define _J1THANKSFORPLAYING_H_

#include "j1Physics.h"
#include "EntityBackground.h"

class EntityEndScreen : public EntityBackground
{
public:

	EntityEndScreen();
	~EntityEndScreen()
	{};

	void Draw();
	void Start();

};


#endif // !
