#include "Level.h"

Level::Level() {

}

void Level::update(float dt) {
	for (auto &e : entities) {
		e->update(dt);
	}
}

void Level::render(sf::RenderWindow &window) {
	for (auto &e : entities) {
		e->render(window);
	}
}

void Level::add_entity(EntityPtr entity) {
	entities.push_back(std::move(entity));
}
