#include "../Game.h"
#include "State.h"
#include "StateIncludes.h"

IdleState::IdleState(Entity &parent)
  : State(parent, "idle"), m_queue(Q_NONE) {
}

std::unique_ptr<State> IdleState::handle_input() {
    sf::Vector2f bp = { (m_parent.dir() == D_RIGHT)
              ? m_parent.x() + m_parent.width() : m_parent.x()
              , m_parent.y() + m_parent.height() };

    if (!m_parent.m_physics->on_ground())
        return std::move(std::unique_ptr<State>(new FallState(m_parent)));

    else if (m_parent.m_input->key_pressed("down")
          && !m_parent.m_input->key_down("roll")
          && !m_parent.m_physics->solid_at_point(bp)
          && animation_id == "idle")
        return std::move(std::unique_ptr<State>(new EdgeLeanState(m_parent)));

    if (!m_parent.m_input->key_down("roll"))
    {
        if      (m_queue == Q_NONE) m_queue = Q_READY;
        else if (m_queue == Q_ROLL) return std::move(
            std::unique_ptr<State>(new RollState(m_parent)));

    }
    else if (m_queue == Q_READY)
        m_queue = Q_ROLL;

    if (m_parent.m_input->key_pressed("jump") && !m_parent.m_input->key_down("roll"))
        return std::move(std::unique_ptr<State>(new JumpState(m_parent)));

    if (animation_id == "idle") {
        if (m_parent.m_input->key_down((m_parent.dir() == D_LEFT) ? "right":"left"))
            m_queue = Q_TURN;

        if (m_parent.m_input->key_down((m_parent.dir() == D_RIGHT) ? "right":"left"))
            return std::move(std::unique_ptr<State>(new WalkState(m_parent)));
    }

    return nullptr;
}

void IdleState::update(float dt) {
    if (!m_parent.m_animation->current_animation()->is_active() && animation_id == "turn-around") {
        m_parent.set_dir((m_parent.dir()==D_RIGHT) ? D_LEFT:D_RIGHT );
        m_parent.m_animation->play_animation_dir(animation_id = "idle");
    }

    if (animation_id == "idle" && m_queue == Q_TURN) {
        m_parent.m_animation->play_animation_dir(animation_id = "turn-around");
        m_queue = Q_NONE;
    }
}
