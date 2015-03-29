#ifndef _SKID_STATE_H_
#define _SKID_STATE_H_ 1

#include <SFML/Graphics.hpp>
#include <string>
#include "State.h"

class SkidState : public State
{
public:
    enum { Q_NONE, Q_ROLL, Q_JUMP };

    SkidState(Entity &parent);

	void update(float dt);
	std::unique_ptr<State> handle_input();

private:
    bool can_q_roll;
    int m_queue;
    sf::Time timer;
};

#endif
