#ifndef _MENU_SCREEN_H_
#define _MENU_SCREEN_H_ 1

#include "Screen.h"

class MenuScreen : public Screen
{
public:
	MenuScreen(Game &game);

	void update(float dt);
	void render(sf::RenderWindow &window);
private:
	void handle_input();
};

#endif
