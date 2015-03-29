#ifndef _DIVE_STATE_H_
#define _DIVE_STATE_H_ 1

#include <memory>
#include "State.h"

class DiveState : public State
{
public:
    DiveState(Entity &parent);

	void update(float dt);
	std::unique_ptr<State> handle_input();

private:
};

#endif
