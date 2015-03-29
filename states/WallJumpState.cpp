#include "../Game.h"
#include "../Logger.h"
#include "State.h"
#include "StateIncludes.h"

WallJumpState::WallJumpState(Entity &parent)
  : State(parent, "prep-jump"), timer(sf::Time::Zero), m_queue(Q_NONE) {
}

std::unique_ptr<State> WallJumpState::handle_input() {
    if (animation_id != "prep-jump") {
        if (m_parent.m_physics->on_ground())
            return std::move(std::unique_ptr<State>(new LandState(m_parent)));

        if (m_parent.m_physics->dy() > 0 || animation_id == "in-air")
            return std::move(std::unique_ptr<State>(new FallState(m_parent)));

        if (!m_parent.m_input->key_down("jump") && timer > sf::seconds(.2)) {
            m_parent.m_physics->set_dy(m_parent.m_physics->dy() / 1.75);
            return std::move(std::unique_ptr<State>(new FallState(m_parent)));
        }

        if (m_queue == Q_DIVE && timer > sf::seconds(.1))
            return std::move(std::unique_ptr<State>(new DiveState(m_parent)));

        if (m_parent.m_input->key_down((m_parent.dir() == D_RIGHT) ? "right":"left") && animation_id == "jump")
        {
            m_parent.m_physics->move(MoveType::WallJump, 5);
        }

        if (m_parent.m_input->key_pressed("dive"))
            m_queue = Q_DIVE;
    }

    return nullptr;
}

void WallJumpState::update(float dt) {
    if (animation_id == "prep-jump") {
        if (m_parent.m_animation->current_animation()->is_active())
            m_parent.m_physics->set_dy(0);
        else
        {
            m_parent.m_animation->play_animation_dir(animation_id = "jump");
            m_parent.m_physics->set_dy(-24);
        }
    }
    else if (animation_id == "jump") {
        timer += sf::seconds(dt);

        if (m_parent.m_animation->current_animation()->is_active())
            m_parent.m_physics->move(MoveType::WallJump, 2.5);
        else
            m_parent.m_animation->play_animation_dir(animation_id = "in-air");
    }
}
