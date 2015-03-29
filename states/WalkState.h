#ifndef _WALK_STATE_H_
#define _WALK_STATE_H_ 1

#include <string>
#include "State.h"
#include <SFML/Graphics.hpp>

class WalkState : public State
{
public:
    WalkState(Entity &parent);

	void update(float dt);
	std::unique_ptr<State> handle_input();

private:
    sf::Time timer, run_timer;
    bool active_run_timer;
};

#endif
