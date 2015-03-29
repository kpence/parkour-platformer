#ifndef _ENTITY_H_
#define _ENTITY_H_ 1

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include "../enums.h"
#include "../components/PhysicsComponent.h"
#include "../components/AnimationComponent.h"
#include "../components/StateComponent.h"
#include "../components/InputComponent.h"

class Screen;

typedef std::unique_ptr<PhysicsComponent> PhysicsPtr;
typedef std::unique_ptr<AnimationComponent> AnimationPtr;
typedef std::unique_ptr<StateComponent> StatePtr;
typedef std::unique_ptr<InputComponent> InputPtr;

class Entity
{
public:
	virtual void update(float dt)                     = 0;
	virtual void render(sf::RenderWindow &window)     = 0;

	virtual ~Entity() { };

	void  set_x(float x);
	void  set_y(float y);
	float x();
	float y();
	void  set_dir(int dir);
	int   dir();
	void  set_width(float width);
	void  set_height(float height);
	float width();
	float height();

	PhysicsPtr      m_physics   = nullptr;
	AnimationPtr    m_animation = nullptr;
	StatePtr        m_state     = nullptr;
	InputPtr        m_input     = nullptr;

protected:
	int          m_direction = 0;
	sf::Vector2f m_position;
	float        m_width  = 0;
	float        m_height = 0;
};

#endif
