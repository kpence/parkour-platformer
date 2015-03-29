#ifndef _IDLE_STATE_H_
#define _IDLE_STATE_H_ 1

#include <memory>
#include "State.h"

class IdleState : public State
{
public:
    enum { Q_NONE, Q_READY, Q_ROLL, Q_TURN };

    IdleState(Entity &parent);

	void update(float dt);
	std::unique_ptr<State> handle_input();

private:
    int m_queue;
};

#endif
