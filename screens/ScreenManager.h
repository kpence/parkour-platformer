#ifndef _SCREEN_MANAGER_H_
#define _SCREEN_MANAGER_H_ 1

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <map>
#include "Screen.h"

typedef std::unique_ptr<Screen> ScreenPtr;

class ScreenManager
{
public:
	ScreenManager();

	void update(float dt);
	void render(sf::RenderWindow &window);

	void add_screen(const std::string &id, ScreenPtr screen);
	void set_active_screen(const std::string &id);
	Screen* active_screen();
private:
	std::map<std::string, ScreenPtr> m_screens;
	Screen *m_activeScreen;
};

#endif
