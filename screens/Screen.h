#ifndef _SCREEN_H_
#define _SCREEN_H_ 1

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "../entities/Entity.h"
#include "../components/InputComponent.h"

typedef std::unique_ptr<InputComponent> InputPtr;

class Game;

class Screen
{
public:
	Screen(Game &game);

	virtual void update(float dt)                   = 0;
	virtual void render(sf::RenderWindow &window)	= 0;
	
	InputPtr m_input = nullptr;

    std::vector<Entity*> solid_entities;

protected:
	Game &game;
	virtual void handle_input() = 0;
};

#endif
