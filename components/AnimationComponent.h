#ifndef _ANIMATION_COMPONENT_H_
#define _ANIMATION_COMPONENT_H_ 1

#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include "Component.h"
#include "../Animation.h"
#include "../enums.h"

class AnimationComponent : public Component
{
public:
	AnimationComponent(Entity* parent);

	sf::Sprite &sprite();

	void update(float dt);
	void render(sf::RenderWindow &window);

	Animation* animation(const std::string &id);
	Animation* current_animation();

	void add_animation(std::string id, sf::Texture &texture, sf::Time frame_time, AnimationType type, bool flipped_x = false);
	void play_animation_dir(const std::string &id);
	void play_animation(const std::string &id, int dir);
	void play_animation(const std::string &id);
	void replay_animation(const std::string &id);
	void play_animation(const std::string &id, sf::Time frame_time);

	void add_frame(const std::string &id, sf::IntRect intrect);
private:
	sf::Sprite m_sprite;
	std::map<std::string, std::unique_ptr<Animation>> m_animations;
	Animation* m_current_animation;
};

#endif
