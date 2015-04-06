#include "../Game.h"
#include "../Logger.h"
#include "State.h"
#include "StateIncludes.h"

JumpState::JumpState(Entity &parent) : State(parent, "prep-jump")
                                     , timer(sf::Time::Zero)
                                     , m_queue(Q_NONE) {
}

std::unique_ptr<State> JumpState::handle_input() {
    if (animation_id != "prep-jump") {
        if (m_parent.m_physics->on_ground())
            return std::move(std::unique_ptr<State>(new LandState(m_parent)));

        if (m_parent.m_physics->dy() > 0)
            return std::move(std::unique_ptr<State>(new FallState(m_parent)));

        if (!m_parent.m_input->key_down("jump") && timer >= sf::seconds(.075)) {
            m_parent.m_physics->set_dy(m_parent.m_physics->dy() / 2);
            return std::move(std::unique_ptr<State>(new FallState(m_parent)));
        }

        if (m_parent.m_input->key_pressed("dive"))
            m_queue = Q_DIVE;

        if (m_queue == Q_DIVE && timer > sf::seconds(.2))
            return std::move(std::unique_ptr<State>(new DiveState(m_parent)));

        for (int dir : {D_RIGHT,D_LEFT})
        if (m_parent.m_input->key_down((dir == D_RIGHT) ? "right":"left"))
        {
            m_parent.m_physics->move(MoveType::AirMove, (m_parent.dir() == dir) ? 1:.4, dir);
        }
    }

    return nullptr;
}

void JumpState::update(float dt) {
    timer += sf::seconds(dt);

    if (!m_parent.m_animation->current_animation()->is_active() && animation_id == "prep-jump") {
        m_parent.m_animation->play_animation_dir(animation_id = "jump");
        m_parent.m_physics->set_dy(-32);
    }

    if (!m_parent.m_animation->current_animation()->is_active() && animation_id == "jump")
        m_parent.m_animation->play_animation_dir(animation_id = "in-air");

}
