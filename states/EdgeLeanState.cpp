#include "../Game.h"
#include "State.h"
#include "StateIncludes.h"

EdgeLeanState::EdgeLeanState(Entity &parent)
  : State(parent, "edge-lean"), bp({0,0}), active(false), turning(false), can_q_roll(false) {
      parent.m_physics->set_dx(parent.m_physics->dx()/4);
}

std::unique_ptr<State> EdgeLeanState::handle_input() {
    if (!m_parent.m_physics->on_ground())
        return std::move(std::unique_ptr<State>(new FallState(m_parent)));

    if (!m_parent.m_input->key_down("roll"))
        can_q_roll = true;
    else if (can_q_roll)
        m_queue = Q_ROLL;

    if (m_parent.m_input->key_pressed("jump") && !m_parent.m_input->key_down("roll"))
        m_queue = Q_JUMP;

    if (timer >= sf::seconds(.2))
        return std::move(std::unique_ptr<State>(new WalkState(m_parent)));

    if (animation_id == "edge-lean" && active)
    {
        // GET_QUEUE_STATE doesn't work here
        if (m_queue == Q_JUMP)
            return std::move(std::unique_ptr<State>(new JumpState(m_parent)));

        if (m_queue == Q_ROLL && !m_parent.m_input->key_down("roll"))
            return std::move(std::unique_ptr<State>(new JumpState(m_parent)));

        if (turning)
            return std::move(std::unique_ptr<State>(new IdleState(m_parent)));

        if (m_parent.m_input->key_pressed((m_parent.dir() == D_LEFT) ? "right":"left"))
            turning = true;

        if (m_parent.m_input->key_pressed((m_parent.dir() == D_RIGHT) ? "right":"left"))
            return std::move(std::unique_ptr<State>(new WalkState(m_parent)));
    }

    return nullptr;
}

void EdgeLeanState::update(float dt) {
    if (active) {
        if (turning)
            m_parent.m_physics->set_dx( (m_parent.dir()==D_RIGHT)? -.2:.2 );

        else if (m_parent.m_input->key_down((m_parent.dir() == D_RIGHT) ? "right":"left")
                    && !m_parent.m_input->key_down("down"))
            timer += sf::seconds(dt);

        if (animation_id == "edge-lean" && turning)
            m_parent.m_animation->play_animation_dir(animation_id = "turn-around");

        if (!m_parent.m_animation->current_animation()->is_active() && animation_id == "turn-around") {
            m_parent.set_dir((m_parent.dir()==D_RIGHT) ? D_LEFT:D_RIGHT );
            m_parent.m_animation->play_animation_dir(animation_id = "edge-lean");
        }
    }
    else {
        bp = { (m_parent.dir() == D_RIGHT)
              ? m_parent.m_physics->dpos().x + m_parent.x() + m_parent.width()/3
              : m_parent.m_physics->dpos().x + m_parent.x() + 2*m_parent.width()/3
              , m_parent.y() + m_parent.height() };
        if (m_parent.m_physics->solid_at_point(bp))
            m_parent.m_physics->set_dx((m_parent.dir() == D_RIGHT)? 1:-1);
        else
            active = true;
    }
}
