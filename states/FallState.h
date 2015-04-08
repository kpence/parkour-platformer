#ifndef _FALL_STATE_H_
#define _FALL_STATE_H_ 1

#include <SFML/Graphics.hpp>
#include <memory>
#include "State.h"

class FallState : public State
{
public:
    FallState(Entity &parent);

	void update(float dt);
	std::unique_ptr<State> handle_input();

private:
    sf::Time timer;
};

#endif
