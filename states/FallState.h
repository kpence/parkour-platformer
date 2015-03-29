#ifndef _FALL_STATE_H_
#define _FALL_STATE_H_ 1

#include <SFML/Graphics.hpp>
#include <memory>
#include "State.h"

class FallState : public State
{
public:
    enum { Q_NONE, Q_READY, Q_JUMP, Q_DIVE };
    FallState(Entity &parent);

	void update(float dt);
	std::unique_ptr<State> handle_input();

private:
    int m_queue;
    sf::Time timer;
};

#endif
