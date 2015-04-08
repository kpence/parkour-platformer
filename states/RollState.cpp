#include "../Game.h"
#include "State.h"
#include "StateIncludes.h"

RollState::RollState(Entity &parent)
  : State(parent, "roll"), timer(sf::Time::Zero), can_q_roll(false) {
      // make parent's attributes for always dodging hit true during middle of roll
}

std::unique_ptr<State> RollState::handle_input() {
    if (timer >= sf::seconds(.1)) {
        allow_change_dir();

        if (!m_parent.m_physics->on_ground())
            return std::move(std::unique_ptr<State>(new FallState(m_parent)));

        // Handle queue
        return std::move(get_queue_state(Q_IDLE));
    }

    // Move
    if ( timer > sf::Time::Zero ) {
        for (int dir : { D_RIGHT, D_LEFT })
         if (m_parent.m_input->key_down((dir == D_RIGHT) ? "right":"left"))
        {
            float f = (m_parent.dir() == dir) ? 2:1;
            m_parent.m_physics->set_dx((dir == D_RIGHT) ? f:-f);
        }
    }

    // q_roll
    if (!m_parent.m_input->key_down("roll"))
        can_q_roll = true;
    else if (can_q_roll)
        m_queue = Q_ROLL;

    // q_jump
    if (m_parent.m_input->key_pressed("jump"))
        m_queue = Q_JUMP;

    return nullptr;
}

void RollState::update(float dt) {
    if (m_parent.m_animation->current_animation()->is_active() && timer == sf::Time::Zero)
        m_parent.m_physics->move(MoveType::Roll, 3);
    else
        timer += sf::seconds(dt);
}
