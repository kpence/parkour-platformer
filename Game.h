#ifndef _GAME_H_
#define _GAME_H_ 1

#include <SFML/Graphics.hpp>
#include <map>
#include "screens/ScreenManager.h"
#include "ResourceHolder.h"

class Game
{
public:
	static Game& instance();

	void run(int width, int height, std::string title);
	void update(float dt);
	void render();

	ScreenManager& screen_manager();

	bool is_running() { return m_isrunning; }
	void close_window() { m_isrunning = false; }
	void set_window_title(const std::string& s) { m_window->setTitle(s); }
	sf::Image capture_window();

	ResourceHolder<sf::Texture, std::string>& texture_holder();

    sf::Vector2f camera_pos,window_size;

    std::vector<sf::Event>* input_events() { return &m_input_events; }

private:
	Game();

	ScreenManager m_scrmanager;

	std::unique_ptr<sf::RenderWindow> m_window;
	
    std::vector<sf::Event> m_input_events;

	bool m_isrunning;

	sf::Clock clock;
	sf::Time deltaTime;

	void load_resources();
	ResourceHolder<sf::Texture, std::string> m_texture_holder;

	Game(Game const&)           = delete;
	void operator=(Game const&) = delete;
};

#endif
