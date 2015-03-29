#include "Screen.h"
#include "../Game.h"

Screen::Screen(Game &game) : game(game) {
	m_input = InputPtr(new InputComponent(NULL));
	m_input->set_events(game.input_events());
}
