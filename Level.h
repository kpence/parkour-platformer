#ifndef _LEVEL_H_
#define _LEVEL_H_ 1

#include "entities/Player.h"

typedef std::unique_ptr<Entity> EntityPtr;

class Level
{
public:
	Level();

	void update(float dt);
	void render(sf::RenderWindow &window);

	void add_entity(EntityPtr entity);
private:
	std::vector<EntityPtr> entities;
};

#endif
