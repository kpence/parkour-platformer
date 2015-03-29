#ifndef _RUN_STATE_H_
#define _RUN_STATE_H_ 1

#include <string>
#include "State.h"
#include <SFML/Graphics.hpp>

class RunState : public State
{
public:
    RunState(Entity &parent);

	void update(float dt);
	std::unique_ptr<State> handle_input();

private:
};

#endif
