#ifndef _SOLID_BLOCK_H_
#define _SOLID_BLOCK_H_ 1

#include "Entity.h"

class SolidBlock : public Entity
{
public:
	SolidBlock(sf::Vector2f pos);
	
	void update(float dt);
	void render(sf::RenderWindow &window);
	void handle_input() { }

private:
};

#endif
