#ifndef _JUMP_STATE_H_
#define _JUMP_STATE_H_ 1

#include <SFML/Graphics.hpp>
#include <memory>
#include "State.h"

class JumpState : public State
{
public:
    JumpState(Entity &parent);

	void update(float dt);
	std::unique_ptr<State> handle_input();

private:
    sf::Time timer;
};

#endif
