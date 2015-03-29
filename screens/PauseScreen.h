#ifndef _PAUSE_SCREEN_H_
#define _PAUSE_SCREEN_H_ 1

#include "Screen.h"

class PauseScreen : public Screen
{
public:
	PauseScreen(Game& game);

	void update(float dt);
	void render(sf::RenderWindow& window);

private:
	void handle_input();

    bool m_active;
    sf::Texture m_tex;
};

#endif
