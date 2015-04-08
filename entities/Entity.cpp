#include "../Logger.h"
#include "Entity.h"

void Entity::set_x(float x) {
	m_position.x = x;
}

void Entity::set_y(float y) {
	m_position.y = y;
}

sf::Vector2f Entity::pos() {
	return m_position;
}

float Entity::x() {
	return m_position.x;
}

float Entity::y() {
	return m_position.y;
}

void Entity::set_dir(int dir) {
	m_direction = dir;
}

int Entity::dir() {
	return m_direction;
}

void Entity::set_width(float width) {
	m_width = width;
}

void Entity::set_height(float width) {
	m_height = width;
}

float Entity::width() {
	return m_width;
}

float Entity::height() {
	return m_height;
}

int Entity::solid_type() {
	return m_solid_type;
}
