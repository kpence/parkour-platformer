#include "../entities/Entity.h"
#include "State.h"
#include "StateIncludes.h"

State::State(Entity &parent, std::string anim_id)
    : m_parent(parent), m_queue(Q_NONE), animation_id(anim_id) { }

void State::allow_change_dir() {
    if (m_parent.m_input->key_down((m_parent.dir() == D_LEFT) ? "right":"left"))
        m_parent.set_dir((m_parent.dir() == D_LEFT) ? D_RIGHT : D_LEFT);
}

std::unique_ptr<State> State::get_queue_state(int otherwise) {
    // NONE / OTHERWISE
    if (m_queue == Q_NONE)
        m_queue = otherwise;

    // IDLE
    if (m_queue == Q_IDLE)
        return std::move(std::unique_ptr<State>(new IdleState(m_parent)));

    // JUMP
    else if (m_queue == Q_JUMP)
        return std::move(std::unique_ptr<State>(new JumpState(m_parent)));

    // DIVE
    else if (m_queue == Q_DIVE)
        return std::move(std::unique_ptr<State>(new DiveState(m_parent)));

    // ROLL
    else if (m_queue == Q_ROLL && !m_parent.m_input->key_down("roll"))
    {
        m_parent.m_animation->play_animation_dir("idle");
        return std::move(std::unique_ptr<State>(new RollState(m_parent)));
    }

    // NONE / OTHERWISE
    m_queue = otherwise;
    return std::move(get_queue_state(Q_IDLE));
}
