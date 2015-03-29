#include "../Game.h"
#include "State.h"
#include "StateIncludes.h"

FallState::FallState(Entity &parent)
  : State(parent, "in-air"), m_queue(Q_NONE), timer(sf::Time::Zero) {
}

std::unique_ptr<State> FallState::handle_input()
{
    if (m_parent.m_physics->on_ground())// && timer > sf::seconds(.05))
        return std::move(std::unique_ptr<State>(new LandState(m_parent)));

    if (m_parent.m_physics->on_ground())
        return std::move(std::unique_ptr<State>(new IdleState(m_parent)));

    for (int dir : {D_RIGHT,D_LEFT})
    if (m_parent.m_input->key_down((dir == D_RIGHT) ? "right":"left"))
    {
        if (m_parent.m_physics->collision_at_dir[dir] && timer != sf::Time::Zero) {
            m_parent.set_dir(dir);
            return std::move(std::unique_ptr<State>(new WallSlideState(m_parent)));
        }

        m_parent.m_physics->move(MoveType::AirMove, (m_parent.dir()==dir) ? 1:.7, dir);
    }

    if ((m_parent.m_input->key_down("dive") || m_queue == Q_DIVE)
            && timer > sf::seconds(.15))
        return std::move(std::unique_ptr<State>(new DiveState(m_parent)));

    if (m_queue == Q_JUMP && timer > sf::seconds(.1) && m_parent.m_physics->m_can_double_jump)
        return std::move(std::unique_ptr<State>(new DoubleJumpState(m_parent)));

    if (m_parent.m_input->key_pressed("jump"))
        m_queue = Q_JUMP;

    if (m_parent.m_input->key_pressed("dive"))
        m_queue = Q_DIVE;

    return nullptr;
}

void FallState::update(float dt) {
    timer += sf::seconds(dt);
}
