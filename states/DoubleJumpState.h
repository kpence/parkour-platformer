#ifndef _DOUBLE_JUMP_STATE_H_
#define _DOUBLE_JUMP_STATE_H_ 1

#include <SFML/Graphics.hpp>
#include <memory>
#include "State.h"

class DoubleJumpState : public State
{
public:
    DoubleJumpState(Entity &parent);

	void update(float dt);
	std::unique_ptr<State> handle_input();

private:
    sf::Time timer;
};

#endif
