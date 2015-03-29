#include "../Game.h"
#include "State.h"
#include "StateIncludes.h"

RunState::RunState(Entity &parent)
  : State(parent, "run") {
}

std::unique_ptr<State> RunState::handle_input() {
    if (!m_parent.m_physics->on_ground())
        return std::move(std::unique_ptr<State>(new FallState(m_parent)));

    if (!m_parent.m_input->key_down("roll"))
        return std::move(std::unique_ptr<State>(new SkidState(m_parent)));

    if (!m_parent.m_input->key_down((m_parent.dir() == D_RIGHT) ? "right":"left"))
        return std::move(std::unique_ptr<State>(new SkidState(m_parent)));

    if (m_parent.m_input->key_pressed("jump"))
        return std::move(std::unique_ptr<State>(new JumpState(m_parent)));

    if (m_parent.m_physics->collision_at_dir[m_parent.dir()])
        return std::move(std::unique_ptr<State>(new SkidState(m_parent)));

    return nullptr;
}

void RunState::update(float dt) {
    m_parent.m_physics->move(MoveType::Run, 5);
}
