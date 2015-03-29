#ifndef _ROLL_STATE_H_
#define _ROLL_STATE_H_ 1

#include <memory>
#include <SFML/Graphics.hpp>
#include "State.h"

class RollState : public State
{
public:
    enum { Q_NONE, Q_ROLL, Q_JUMP };

    RollState(Entity &parent);

	void update(float dt);
	std::unique_ptr<State> handle_input();

private:
    sf::Time timer;
    bool can_q_roll;
    int m_queue;
};

#endif
