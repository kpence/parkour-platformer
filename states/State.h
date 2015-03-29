#ifndef _STATE_H_
#define _STATE_H_ 1

#include <memory>
#include <string>
#include "../enums.h"

class Entity;
class Game;

class State {
protected:
	Entity &m_parent;

    void allow_change_dir();

public:
    State(Entity &parent, std::string anim_id) : m_parent(parent), animation_id(anim_id) { }
	virtual ~State() { };

	virtual void update(float dt)                  = 0;
	virtual std::unique_ptr<State> handle_input()  = 0;

	std::string animation_id;
};

#endif
