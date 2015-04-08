#ifndef _ANIMATION_H_
#define _ANIMATION_H_ 1

#include <string>
#include <SFML/Graphics.hpp>

enum AnimationType {
	ONCE,
	LOOP
};

class Animation
{
public:
	Animation(sf::Texture &texture);

	void update(float dt);

	void add_frame(sf::IntRect intrect);
	void add_frame(sf::IntRect grid_rect, sf::IntRect crop_rect);
	void add_frame(int col, int row, int w, int h);
	sf::IntRect current_frame();
	int frame_size();
    bool is_active();

	sf::Time frame_time;
	sf::Texture& texture;
    bool flip_x;
	int m_width, m_height;

	AnimationType animation_type;

	int frame_index;
	sf::Time get_timer();
    void activate();
    void reset();

private:
	std::vector<sf::IntRect> frames;
	int m_frame_size;

	sf::Time timer;
	bool active;
};

#endif
