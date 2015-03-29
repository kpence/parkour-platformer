#ifndef _LAND_STATE_H_
#define _LAND_STATE_H_ 1

#include <SFML/Graphics.hpp>
#include <memory>
#include "State.h"

class LandState : public State
{
public:
    enum { Q_NONE, Q_ROLL, Q_JUMP };

    LandState(Entity &parent);

	void update(float dt);
	std::unique_ptr<State> handle_input();

private:
    sf::Time timer;
    int m_queue;
    bool finished, can_q_roll;
};

#endif
