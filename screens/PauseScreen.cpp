#include "PauseScreen.h"
#include "../Game.h"

PauseScreen::PauseScreen(Game& game) : Screen(game) {
}

void PauseScreen::update(float dt) {
    if (!m_active) {
        m_tex.loadFromImage(Game::instance().capture_window());
        m_active = true;
    }
	else handle_input();
}

void PauseScreen::render(sf::RenderWindow& window) {
    sf::Sprite spr;
	spr.setTexture(m_tex);
    window.draw(spr);
}

void PauseScreen::handle_input() {
	if (m_input->key_pressed(std::vector<std::string>{"pause","cancel"})) {
		Game::instance().screen_manager().set_active_screen("game");
        m_active = false;
	}
}
