#include "Game.h"
#include "Assets.h"
#include "screens/MenuScreen.h"
#include "screens/GameScreen.h"
#include "screens/PauseScreen.h"

sf::Sprite sprite;

// Private constructor
Game::Game() {
    camera_pos = {0,0};
    window_size = {640,480};
}

// Get a reference to the static instance of this class
Game& Game::instance() {
	static Game instance;
	return instance;
}

void Game::run(int width, int height, std::string title) {
	load_resources();

	m_window = std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(width, height), title));
    m_window->setKeyRepeatEnabled(false);

	m_scrmanager.add_screen("menu", ScreenPtr(new MenuScreen(*this)));
	m_scrmanager.add_screen("game", ScreenPtr(new GameScreen(*this)));
	m_scrmanager.add_screen("pause", ScreenPtr(new PauseScreen(*this)));
	m_scrmanager.set_active_screen("menu");

	m_isrunning = true;
}

void Game::update(float dt) {
    sf::Event event;
    m_input_events.clear();

	while (m_window->pollEvent(event)) {

		if (event.type == sf::Event::Closed) {
            m_isrunning = false;
            m_window->close();
        }
		else if (event.type == sf::Event::Resized) {
			sf::Vector2u ws(m_window->getSize());
            window_size = {float(ws.x), float(ws.y)};
            m_window->setView(sf::View(
                sf::FloatRect(0.f,0.f, window_size.x,window_size.y) ));
        }

        m_input_events.push_back(event);

	}

	m_scrmanager.update(dt);
}

void Game::render() {
	m_window->clear();

	m_scrmanager.render(*m_window);

	m_window->display();
}

sf::Image Game::capture_window() {
    return m_window->capture();
}

ScreenManager& Game::screen_manager() {
	return m_scrmanager;
}

void Game::load_resources() {
	m_texture_holder.load("player", "assets/textures/player.png");
	m_texture_holder.load("block", "assets/textures/block.png");
}

ResourceHolder<sf::Texture, std::string>& Game::texture_holder() {
	return m_texture_holder;
}
