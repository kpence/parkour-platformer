#include "SolidBlock.h"
#include "../Game.h"
#include "../Logger.h"

#define BLOCK_TEXTURE Game::instance().texture_holder().get("block")

using sf::Keyboard;

SolidBlock::SolidBlock(sf::Vector2f pos) {
	m_animation = AnimationPtr(new AnimationComponent(this));
    set_x(pos.x);
    set_y(pos.y);
	
	set_width(40);
	set_height(40);

	m_animation->add_animation("normal", BLOCK_TEXTURE, sf::seconds(1), AnimationType::LOOP);
	m_animation->animation("normal")->add_frame(sf::IntRect(0, 0, 40, 40));
	m_animation->play_animation("normal");
}

void SolidBlock::update(float dt) {
	m_animation->update(dt);
}

void SolidBlock::render(sf::RenderWindow &window) {
	m_animation->render(window);
}

