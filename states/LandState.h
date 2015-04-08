#ifndef _LAND_STATE_H_
#define _LAND_STATE_H_ 1

#include <SFML/Graphics.hpp>
#include <memory>
#include "State.h"

class LandState : public State
{
public:
    LandState(Entity &parent);

	void update(float dt);
	std::unique_ptr<State> handle_input();

private:
    sf::Time timer;
    bool finished, can_q_roll;
};

#endif
