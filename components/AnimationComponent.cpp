#include "AnimationComponent.h"
#include "../Game.h"
#include "../Logger.h"
#include "../entities/Entity.h"

AnimationComponent::AnimationComponent(Entity* parent) : Component(parent) {
	m_current_animation = nullptr;
}

void AnimationComponent::update(float dt) {
    int x = m_parent->x();
    x += (m_current_animation->flip_x)? m_parent->width() : 0;

    auto& cam = Game::instance().camera_pos;

	m_sprite.setPosition(x-cam.x, m_parent->y()-cam.y);

	if (m_current_animation != nullptr)
		m_current_animation->update(dt);

}

void AnimationComponent::render(sf::RenderWindow &window) {
	window.draw(m_sprite);
}

void AnimationComponent::add_animation(std::string id, sf::Texture &texture, sf::Time frame_time, AnimationType type, bool flipped_x) {
	m_animations[id] = std::move(std::unique_ptr<Animation>(new Animation(texture)));
	m_animations[id]->frame_time = frame_time;
	m_animations[id]->animation_type = type;
	m_animations[id]->flip_x = flipped_x;
}

Animation* AnimationComponent::current_animation() {
	return m_current_animation;
}

Animation* AnimationComponent::animation(const std::string &id) {
	return m_animations[id].get();
}

void AnimationComponent::replay_animation(const std::string &id) {
    m_animations[id]->reset();
    play_animation(id);
}

void AnimationComponent::play_animation_dir(const std::string &id) {
    play_animation(id, m_parent->dir());
}

void AnimationComponent::play_animation(const std::string &id, int dir) {
    std::string lid(id), rid((dir == D_RIGHT)?":right":":left");
    play_animation(lid+rid);
}

void AnimationComponent::play_animation(const std::string &id, sf::Time frame_time) {
    play_animation(id);
    m_current_animation->frame_time = frame_time;
}

void AnimationComponent::play_animation(const std::string &id) {
    if (m_current_animation != nullptr && m_current_animation != m_animations[id].get()) {
        m_current_animation->reset();
    }

    m_animations[id]->activate();
    m_sprite.setTexture(m_animations[id]->texture);
    m_sprite.setTextureRect(m_animations[id]->current_frame());

    m_sprite.setScale((m_animations[id]->flip_x) ? -1.f:1.f,1.f);

    m_current_animation = m_animations[id].get();
    m_current_animation->activate();
}
