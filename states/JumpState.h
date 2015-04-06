#ifndef _JUMP_STATE_H_
#define _JUMP_STATE_H_ 1

#include <SFML/Graphics.hpp>
#include <memory>
#include "State.h"

class JumpState : public State
{
public:
    enum { Q_NONE, Q_DIVE };

    JumpState(Entity &parent);

	void update(float dt);
	std::unique_ptr<State> handle_input();

private:
    sf::Time timer;
    int m_queue;
};

#endif
