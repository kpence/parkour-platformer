#include "../Game.h"
#include "State.h"
#include "StateIncludes.h"

RollState::RollState(Entity &parent)
  : State(parent, "roll"), timer(sf::Time::Zero), can_q_roll(false), m_queue(Q_NONE) {
      // make parent's attributes for always dodging hit true during middle of roll
}

std::unique_ptr<State> RollState::handle_input() {
    if (!m_parent.m_physics->on_ground())
        return std::move(std::unique_ptr<State>(new FallState(m_parent)));

    if (timer >= sf::seconds(.1)) {
        allow_change_dir();

        // IDLE
        if (m_queue == Q_NONE)
            return std::move(std::unique_ptr<State>(new IdleState(m_parent)));

        // JUMP
        else if (m_queue == Q_JUMP)
            return std::move(std::unique_ptr<State>(new JumpState(m_parent)));

        // ROLL
        else if (!m_parent.m_input->key_down("roll") && m_queue == Q_ROLL)
        {
            m_parent.m_animation->play_animation_dir("idle");
            return std::move(std::unique_ptr<State>(new RollState(m_parent)));
        }

        // Otherwise: IDLE
        return std::move(std::unique_ptr<State>(new IdleState(m_parent)));
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
