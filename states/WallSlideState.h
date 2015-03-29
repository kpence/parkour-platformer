#ifndef _WALL_SLIDE_STATE_H_
#define _WALL_SLIDE_STATE_H_ 1

#include <SFML/Graphics.hpp>
#include <memory>
#include "State.h"

class WallSlideState : public State
{
public:
    WallSlideState(Entity &parent);

	void update(float dt);
	std::unique_ptr<State> handle_input();

private:
    sf::Time timer;
};

#endif
