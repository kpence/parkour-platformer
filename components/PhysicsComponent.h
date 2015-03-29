#ifndef _PHYSICS_COMPONENT_H_
#define _PHYSICS_COMPONENT_H_ 1

#include <SFML/Graphics.hpp>
#include <array>
#include "Component.h"
#include "../enums.h"

class Entity;

class PhysicsComponent : public Component
{
public:
	PhysicsComponent(Entity* parent);

    // Collision
    bool on_ground();
    void store_collisions_at_point(float x, float y);

    bool solid_at_bottom_point();
    bool solid_at_point(float x, float y);
    bool solid_at_point(const sf::Vector2f& point);

	bool collision_at_dir[D_COUNT];

    // Speed
	void set_friction(float f);
	void set_speed(float s);
	void set_dx(float d);
	void set_dy(float d);
	sf::Vector2f dpos();
	float dx();
	float dy();

	float m_h_speed;
	float m_v_speed;
	float m_max_h_speed;
	float m_max_v_speed;
	float m_gravity;
	float m_friction;

    // Movement
    std::array<float, MoveType::Count> m_max_speeds;
    void move(int type, float acceleration, int dir = D_COUNT);
    void move_dir(float acceleration, int dir);

	void set_position(sf::Vector2f pos);
	void update_position(sf::Vector2f& pos);
	void update(float dt);

    bool m_can_double_jump;

private:
	sf::Vector2f m_dpos;
	float m_dx;
	float m_dy;
};

#endif
