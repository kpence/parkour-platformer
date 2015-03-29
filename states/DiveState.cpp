#include "../Game.h"
#include "State.h"
#include "StateIncludes.h"

DiveState::DiveState(Entity &parent)
  : State(parent, "dive")
{
    if (m_parent.m_input->key_down((parent.dir() == D_LEFT) ? "right":"left"))
        parent.set_dir((parent.dir() == D_LEFT) ? D_RIGHT:D_LEFT);

    if (parent.m_physics->dy() < 0) parent.m_physics->set_dy(parent.m_physics->dy()/4 + 1);
    else                            parent.m_physics->set_dy(parent.m_physics->dy()   + 1);
}

std::unique_ptr<State> DiveState::handle_input() {
    if (m_parent.m_physics->on_ground())
    {
        if (m_parent.m_input->key_down((m_parent.dir() == D_LEFT) ? "right":"left"))
            m_parent.set_dir((m_parent.dir() == D_LEFT) ? D_RIGHT:D_LEFT);

        return std::move(std::unique_ptr<State>(new RollState(m_parent)));
    }

    for (int dir : {D_RIGHT,D_LEFT})
    if (m_parent.m_input->key_down((dir == D_RIGHT) ? "right":"left"))
    {
         m_parent.m_physics->move(MoveType::AirMove, (m_parent.dir()==dir) ? 1:.3, dir);
    }

    return nullptr;
}

void DiveState::update(float dt) {
}
