#ifndef _PLAYER_H_
#define _PLAYER_H_ 1

#include "Entity.h"

class Player : public Entity
{
public:
	Player();
	
	void update(float dt);
	void render(sf::RenderWindow &window);

private:
};

#endif
