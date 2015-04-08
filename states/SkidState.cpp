#include "../Game.h"
#include "State.h"
#include "StateIncludes.h"

SkidState::SkidState(Entity &parent)
  : State(parent, "skid"), can_q_roll(false), timer(sf::Time::Zero)
{
    parent.m_physics->set_friction(1);
}

std::unique_ptr<State> SkidState::handle_input() {
    if (!m_parent.m_physics->on_ground()) {
        m_parent.m_physics->set_friction(1.5);
        return std::move(std::unique_ptr<State>(new FallState(m_parent)));
    }

    if ( (timer >= sf::seconds(.05) || m_queue != Q_NONE)
        && (m_parent.m_physics->dx() < .2 && m_parent.m_physics->dx() > -.2) )
    {
        allow_change_dir();
        m_parent.m_physics->set_friction(1.5);

        // Handle queue
        return std::move(get_queue_state(Q_IDLE));
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

void SkidState::update(float dt) {
    if (m_parent.m_physics->dx() < .2 && m_parent.m_physics->dx() > -.2)
        timer += sf::seconds(dt);
    else
        m_parent.m_physics->m_friction += .03;

    m_parent.m_physics->move(MoveType::Skid, 5);

}
