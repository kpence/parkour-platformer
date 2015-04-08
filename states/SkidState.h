#ifndef _SKID_STATE_H_
#define _SKID_STATE_H_ 1

#include <SFML/Graphics.hpp>
#include <string>
#include "State.h"

class SkidState : public State
{
public:
    SkidState(Entity &parent);

	void update(float dt);
	std::unique_ptr<State> handle_input();

private:
    bool can_q_roll;
    sf::Time timer;
};

#endif
