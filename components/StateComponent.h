#ifndef _STATE_COMPONENT_H_
#define _STATE_COMPONENT_H_ 1

#include <memory>
#include <string>
#include "Component.h"
#include "../enums.h"
#include "../states/State.h"

class State;

class StateComponent : public Component
{
public:
	StateComponent(Entity* parent);

	void update(float dt);
	void handle_input();

	State* state();
	void set_state(std::unique_ptr<State> sp);

private:
	std::unique_ptr<State> m_state;

};

#endif
