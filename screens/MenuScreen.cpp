#include "MenuScreen.h"
#include "../Game.h"

MenuScreen::MenuScreen(Game &game) : Screen(game) {
}

void MenuScreen::update(float dt) {
	handle_input();
}

void MenuScreen::render(sf::RenderWindow &window) {
	window.clear(sf::Color::Blue);	
}

void MenuScreen::handle_input() {
	if (m_input->key_pressed(sf::Keyboard::Space))
		Game::instance().screen_manager().set_active_screen("game");

}
