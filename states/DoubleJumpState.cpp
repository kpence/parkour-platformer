#include "../Game.h"
#include "State.h"
#include "StateIncludes.h"

DoubleJumpState::DoubleJumpState(Entity &parent)
  : State(parent, "jump"), timer(sf::Time::Zero) {
      parent.m_physics->set_dy(-24);
      parent.m_physics->set_dx(parent.m_physics->dx()/3);
      parent.m_physics->m_can_double_jump = false;
}

std::unique_ptr<State> DoubleJumpState::handle_input() {
    if (m_parent.m_physics->on_ground())
        return std::move(std::unique_ptr<State>(new LandState(m_parent)));

    if (m_parent.m_physics->dy() > 0)
        return std::move(std::unique_ptr<State>(new FallState(m_parent)));

    if (!m_parent.m_input->key_down("jump")) {
        m_parent.m_physics->set_dy(m_parent.m_physics->dy() / 2);
        return std::move(std::unique_ptr<State>(new FallState(m_parent)));
    }

    if (m_parent.m_input->key_pressed("dive") && timer > sf::seconds(.1))
        return std::move(std::unique_ptr<State>(new DiveState(m_parent)));

    for (int dir : {D_RIGHT,D_LEFT})
    if (m_parent.m_input->key_down((dir == D_RIGHT) ? "right":"left"))
    {
        m_parent.m_physics->move(MoveType::AirMove, (m_parent.dir() == dir) ? 1:.3, dir);
    }

    return nullptr;
}

void DoubleJumpState::update(float dt) {
    if (!m_parent.m_animation->current_animation()->is_active() && animation_id == "jump")
        m_parent.m_animation->play_animation_dir(animation_id = "in-air");

    timer += sf::seconds(dt);
}
