#include <algorithm>
#include "GameScreen.h"
#include "../Game.h"

GameScreen::GameScreen(Game& game) : Screen(game) {
    m_player_test = std::unique_ptr<Player>(new Player); //TODO testing
	m_player_test->m_input->set_events(game.input_events());

    for (int i = 0; i < 10; ++i) {
        m_test_blocks.push_back(std::unique_ptr<SolidBlock>(new SolidBlock({float(i)*32,192+200}))); //TODO testing
        solid_entities.push_back(&*(m_test_blocks.back()));
    }
    for (int i = 0; i < 10; ++i) {
        m_test_blocks.push_back(std::unique_ptr<SolidBlock>(new SolidBlock({float(i)*32+160,192+64+200}))); //TODO testing
        solid_entities.push_back(&*(m_test_blocks.back()));
    }
    for (int i = 0; i < 100; ++i) {
        if (i > 80 || i < 27) {
            m_test_blocks.push_back(std::unique_ptr<SolidBlock>(new SolidBlock({float(i)*32,192+192+200}))); //TODO testing
            solid_entities.push_back(&*(m_test_blocks.back()));
        }
        m_test_blocks.push_back(std::unique_ptr<SolidBlock>(new SolidBlock({float(i)*32,192+392+200+(32*float(floor(i/40)))}))); //TODO testing
        solid_entities.push_back(&*(m_test_blocks.back()));
    }
    for (int i = 0; i < 5; ++i) {
        m_test_blocks.push_back(std::unique_ptr<SolidBlock>(new SolidBlock({float(i)*32+240,192+96+200}))); //TODO testing
        solid_entities.push_back(&*(m_test_blocks.back()));
    }
    for (int i = 0; i < 100; ++i) {
        m_test_blocks.push_back(std::unique_ptr<SolidBlock>(new SolidBlock({32*32,192+192-float(i)*32+200}))); //TODO testing
        solid_entities.push_back(&*(m_test_blocks.back()));
    }

}

void GameScreen::update(float dt) {
	m_player_test->update(dt); //TODO testing
    for (auto& m : m_test_blocks) m->update(dt);

    // For debuging
    if (m_input->key_pressed(sf::Keyboard::Space))
        m_player_test->set_y(0);

    // Input
	if (m_input->key_pressed("pause")) {
		Game::instance().screen_manager().set_active_screen("pause");
        Game::instance().screen_manager().active_screen()->update(dt);
    }
    else handle_input();

}

void GameScreen::render(sf::RenderWindow &window) {
    // center camera
    auto& ws = Game::instance().window_size;
    auto& cam = Game::instance().camera_pos;
    cam = { (cam.x + m_player_test->x() - ws.x/2)/2
           , (cam.y + m_player_test->y() - ws.y/2)/2 };
    if (cam.x < 0) cam.x = 0;
    if (cam.y < 0) cam.y = 0;

	window.clear(sf::Color(56,94,142));

	m_player_test->render(window); //TODO testing
    for (auto& m : m_test_blocks) m->render(window);
}

void GameScreen::handle_input() {
}
