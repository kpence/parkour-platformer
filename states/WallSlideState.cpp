#include "../Game.h"
#include "../Logger.h"
#include "State.h"
#include "StateIncludes.h"

WallSlideState::WallSlideState(Entity &parent)
  : State(parent, "wall-slide"), timer(sf::Time::Zero) {
    if (parent.m_physics->dy() > 0)
        parent.m_physics->set_dy(parent.m_physics->dy()/3);
}

std::unique_ptr<State> WallSlideState::handle_input() {
    if (timer > sf::seconds(.1))
    {
        if (!m_parent.m_physics->collision_at_dir[m_parent.dir()]) {
            m_parent.set_dir((m_parent.dir() == D_LEFT) ? D_RIGHT:D_LEFT);
            return std::move(std::unique_ptr<State>(new FallState(m_parent)));
        }

        if (m_parent.m_physics->on_ground()) {
            m_parent.set_dir((m_parent.dir() == D_LEFT) ? D_RIGHT:D_LEFT);
            return std::move(std::unique_ptr<State>(new LandState(m_parent)));
        }
    }

    if (m_parent.m_input->key_pressed("jump")) {
        m_parent.set_dir((m_parent.dir() == D_LEFT) ? D_RIGHT:D_LEFT);
        m_parent.m_physics->set_dx(0);
        m_parent.m_physics->move(MoveType::AirMove, 10);
        return std::move(std::unique_ptr<State>(new WallJumpState(m_parent)));
    }

    if (!m_parent.m_input->key_down((m_parent.dir() == D_RIGHT) ? "right":"left"))
        return std::move(std::unique_ptr<State>(new FallState(m_parent)));

    return nullptr;
}

void WallSlideState::update(float dt) {
    timer += sf::seconds(dt);
}
