#include "../Game.h"
#include "../Logger.h"
#include "State.h"
#include "StateIncludes.h"

WalkState::WalkState(Entity &parent)
  : State(parent, "init-walk"), timer(sf::Time::Zero), run_timer(sf::Time::Zero), active_run_timer(false) {
}

std::unique_ptr<State> WalkState::handle_input() {
    sf::Vector2f bp = { (m_parent.dir() == D_RIGHT)
              ? m_parent.m_physics->dpos().x + m_parent.x() + m_parent.width()/3
              : m_parent.m_physics->dpos().x + m_parent.x() + 2*m_parent.width()/3
              , m_parent.y() + m_parent.height() };

    if (!m_parent.m_physics->on_ground())
        return std::move(std::unique_ptr<State>(new FallState(m_parent)));

    else
    if (!m_parent.m_input->key_down("roll")
          && m_parent.m_input->key_down("down")
          && !m_parent.m_physics->solid_at_point(bp)
          && timer > sf::seconds(.15))
        return std::move(std::unique_ptr<State>(new EdgeLeanState(m_parent)));

    if (m_parent.m_input->key_down("roll") && !active_run_timer)
        active_run_timer = true;

    if (run_timer >= sf::seconds(.25))
        return std::move(std::unique_ptr<State>(new RunState(m_parent)));

    if (!m_parent.m_input->key_down("roll") && active_run_timer)
        return std::move(std::unique_ptr<State>(new RollState(m_parent)));

    if (m_parent.m_input->key_pressed("jump"))
        return std::move(std::unique_ptr<State>(new JumpState(m_parent)));

    if (!m_parent.m_input->key_down((m_parent.dir() == D_RIGHT) ? "right":"left"))
        return std::move(std::unique_ptr<State>(new IdleState(m_parent)));

    return nullptr;
}

void WalkState::update(float dt) {
    bool blocked = m_parent.m_physics->collision_at_dir[m_parent.dir()];

    // Animations
    if (!m_parent.m_animation->current_animation()->is_active() && animation_id == "init-walk")
        m_parent.m_animation->play_animation_dir(animation_id = "walk");

    if (blocked)
    {
        if (animation_id == "walk" || animation_id == "init-walk")
            m_parent.m_animation->play_animation_dir(animation_id = "idle");
    }
    else if (animation_id == "idle")
        m_parent.m_animation->play_animation_dir(animation_id = "init-walk");

    // Timers
    timer += sf::seconds(dt);

    if (active_run_timer && !blocked)
        run_timer += sf::seconds(dt);

    m_parent.m_physics->move(MoveType::Walk, 2);
}
