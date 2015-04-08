#ifndef _STATE_H_
#define _STATE_H_ 1

#include <memory>
#include <string>
#include "../enums.h"

class Entity;
class Game;

class State {
protected:
    enum { Q_NONE, Q_READY, Q_TURN, Q_ROLL, Q_JUMP, Q_DIVE, Q_IDLE };

	Entity &m_parent;
    int m_queue;

    void allow_change_dir();
	std::unique_ptr<State> get_queue_state(int otherwise);

public:
    State(Entity &parent, std::string anim_id);
	virtual ~State() { };

	virtual void update(float dt)                 = 0;
	virtual std::unique_ptr<State> handle_input() = 0;

	std::string animation_id;
};

#endif
