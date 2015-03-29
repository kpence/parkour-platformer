#ifndef _EDGE_LEAN_STATE_H_
#define _EDGE_LEAN_STATE_H_ 1

// This state occurs when the entity is stopped
// from walking off the edge of the platform
//
// From this state you can:
// Key -> New State
// "Jump" -> Jump
// "Down" -> EdgeGrab
// "<Key of opposite direction>" -> Idle
// "<Key of current direction>" -> Walk

#include <SFML/Graphics.hpp>
#include <memory>
#include "State.h"

class EdgeLeanState : public State
{
public:
    enum { Q_NONE, Q_TURN, Q_ROLL, Q_JUMP };

    EdgeLeanState(Entity &parent);

	void update(float dt);
	std::unique_ptr<State> handle_input();

private:
    sf::Time timer;
    sf::Vector2f bp;
    bool active, turning, can_q_roll;
    int m_queue;
};

#endif
