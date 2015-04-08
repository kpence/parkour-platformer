#include "Animation.h"
#include "Logger.h"

Animation::Animation(sf::Texture &texture)
    : frame_time(sf::seconds(.1)), texture(texture), flip_x(false), m_width(0), m_height(0)
    , frame_index(0), m_frame_size(0), active(false) {
}

void Animation::update(float dt) {
    if (animation_type == AnimationType::LOOP)
        active = true;

	if (active) {
		timer += sf::seconds(dt);

		if (timer >= frame_time)
        {
			timer = sf::Time::Zero;

			if (frame_index + 1 < frame_size()) ++frame_index;
            else
            {
				if (animation_type == AnimationType::ONCE)
					active = false;

				frame_index = 0;
			}
		}

	}
}

void Animation::add_frame(sf::IntRect intrect) {
    m_width = intrect.width;
    m_height = intrect.height;
    ++m_frame_size;
	frames.push_back(intrect);
}

void Animation::add_frame(sf::IntRect grid_rect, sf::IntRect crop_rect) {
    int col = grid_rect.left, row = grid_rect.top
        , w = grid_rect.width,  h = grid_rect.height;
    add_frame(sf::IntRect( crop_rect.left+col*w, crop_rect.top+row*h
             , crop_rect.width-crop_rect.left, crop_rect.height-crop_rect.top ));
}

void Animation::add_frame(int col, int row, int w, int h) {
    add_frame(sf::IntRect(col*w, row*h, w, h));
}

sf::IntRect Animation::current_frame() {
	return frames[frame_index];
}

int Animation::frame_size() {
    return m_frame_size;
}
bool Animation::is_active() {
    return active;
}

void Animation::reset() {
    frame_index = 0;
    timer = sf::Time::Zero;
    active = false;
}

void Animation::activate() {
    if (!active) {
        frame_index = 0;
        timer = sf::Time::Zero;
    }
    active = true;
}

sf::Time Animation::get_timer() {
    return timer;
}
