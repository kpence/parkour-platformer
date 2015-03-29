#include "StateComponent.h"
#include "../states/State.h"
#include "../Logger.h"
#include "../entities/Entity.h"
#include "../Animation.h"
#include "../states/IdleState.h"

StateComponent::StateComponent(Entity* parent) : Component(parent) {
	m_state = std::move(std::unique_ptr<State>(new IdleState(*parent)));
}

void StateComponent::update(float dt) {
    std::string s;
	if (m_state != nullptr) {
		m_state->update(dt);
        s = state()->animation_id; s += (m_parent->dir() == D_RIGHT) ? ":right":":left";
        if (m_parent->m_animation->current_animation() != m_parent->m_animation->animation(s)
         || m_parent->m_animation->current_animation()->is_active()
         || m_parent->m_animation->current_animation()->animation_type == AnimationType::LOOP) {
            m_parent->m_animation->play_animation_dir(state()->animation_id);
        }
	}
}

void StateComponent::handle_input() {
	if (m_state != nullptr) {
		auto new_state = std::move(m_state->handle_input());
        if (new_state != nullptr)
            m_state = std::move(new_state);
	}
}

void StateComponent::set_state(std::unique_ptr<State> sp) {
	m_state = std::move(sp);
}

State* StateComponent::state() {
	return m_state.get();
}
