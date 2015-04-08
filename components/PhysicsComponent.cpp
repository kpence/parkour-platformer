#include <algorithm>
#include "PhysicsComponent.h"
#include "../Logger.h"
#include "../Game.h"
#include "../screens/Screen.h"
#include "../entities/Entity.h"

PhysicsComponent::PhysicsComponent(Entity* parent) : Component(parent)
    , m_h_speed(100), m_v_speed(32), m_max_h_speed(3.5), m_max_v_speed(30), m_gravity(1.5), m_friction(1.5)
    , m_can_double_jump(true), m_dropping(false)
    , m_dpos({0,0}), m_dx(0), m_dy(0)
{
    m_max_speeds[MoveType::Move]     = 3.5;
    m_max_speeds[MoveType::Walk]     = 4.5;
    m_max_speeds[MoveType::Run]      = 11;
    m_max_speeds[MoveType::Roll]     = 7;
    m_max_speeds[MoveType::AirMove]  = 6;
    m_max_speeds[MoveType::WallJump] = 7;
    for (auto& cd : collision_at_dir) cd = true;
}

void PhysicsComponent::update(float dt) {
    /* Hitting walls */
    if ( (collision_at_dir[D_LEFT] && m_dx < 0)
      || (collision_at_dir[D_RIGHT] && m_dx > 0) )
        m_dx = 0;

	m_dpos = {(m_h_speed*dt) * m_dx, (m_v_speed*dt) * m_dy};

    /* Detecting collision */
    for (auto& cd : collision_at_dir) cd = false;
    store_collisions_at_point(m_parent->x(), m_parent->y());

    /* actual movement */
    m_parent->set_x(m_parent->x()+m_dpos.x);
    m_parent->set_y(m_parent->y()+m_dpos.y);

    // Gravity
    if (m_gravity+m_dy < m_max_v_speed)
        m_dy = std::min(m_dy+m_gravity, m_max_v_speed);

    /* Friction and double jump reset */
    if (on_ground()) {
        m_dx /= m_friction;
        m_can_double_jump = true;
    }

}

bool PhysicsComponent::on_ground() {
	return collision_at_dir[D_DOWN];
}

bool PhysicsComponent::solid_at_point(const sf::Vector2f& point) {
    return solid_at_point(point.x, point.y);
}

bool PhysicsComponent::solid_at_point(float x, float y) {
    for (auto& se : Game::instance().screen_manager().active_screen()->solid_entities)
    {
        sf::IntRect box(int(se->x()), int(se->y()), int(se->width()), int(se->height()));
        if (box.contains(x,y)) return true;
    }
    return false;
}

void PhysicsComponent::store_collisions_at_point(float x, float y)
{
	sf::Vector2f pp = {x + m_parent->width(), m_parent->y() + m_parent->height()};

    /* Collision detection */
    for (auto& se : Game::instance().screen_manager().active_screen()->solid_entities) {
        if (m_parent == se) continue;
        if (m_dy == 0 && m_dx == 0) break;

        if (se->solid_type() == SolidType::Droppable && m_dropping) continue;

        sf::Vector2f sp = {se->x() + se->width(), se->y() + se->height()};
        /*Checking vertical collision*/
        if ( m_parent->x() < sp.x && pp.x > se->x() )
        {
            /* Hitting ceiling */
            if (!collision_at_dir[D_UP] && m_dy < 0 && se->solid_type() != SolidType::Droppable
                 && (m_parent->y() < sp.y  ||  m_parent->y()+m_dpos.y < sp.y) && m_parent->y() > sp.y)
            {
                m_dpos.y = std::max(1 + se->y() + se->height() - m_parent->y(), m_dpos.y);
                collision_at_dir[D_UP] = true;
                m_dy /= 2;
            }

            /* Landing */
            if (!collision_at_dir[D_DOWN] && m_dy >= 0
                 && (pp.y + m_dpos.y+1) >= se->y() && pp.y <= se->y())
            {
                m_dpos.y = std::min(se->y() - m_parent->height() - m_parent->y(), m_dpos.y);
                collision_at_dir[D_DOWN] = true;
                m_dy = 0;
            }

        }

        if (se->solid_type() == SolidType::Droppable) continue;

        int gpy = (on_ground()) ? pp.y : pp.y+m_dpos.y;

        /*Checking horozontally*/
        if ( (m_parent->y()+m_dpos.y <= sp.y && gpy  > se->y())
                 || (m_parent->y() <= sp.y && pp.y > se->y()) )
        {
            /* Hit right */
            if (!collision_at_dir[D_RIGHT] && m_dx >= 0
                 && (pp.x + m_dpos.x + 1) >= se->x() && pp.x <= se->x())
            {
                collision_at_dir[D_RIGHT] = true;
                m_dpos.x = std::min(se->x() - m_parent->width() - m_parent->x(), m_dpos.x);
                m_dx = 0;
            }

            /* Hit left */
            if (!collision_at_dir[D_LEFT] && m_dx <= 0
                 && (m_parent->x() + m_dpos.x - 1) <= sp.x && m_parent->x() >= sp.x)
            {
                collision_at_dir[D_LEFT] = true;
                m_dpos.x = std::max(se->x() + se->width() - m_parent->x(), m_dpos.x);
                m_dx = 0;
            }
        }

    }
}

void PhysicsComponent::move(int type, float a, int dir) {
    m_max_h_speed = m_max_speeds[type];

    move_dir(a, (dir == D_COUNT) ? m_parent->dir() : dir);
}

void PhysicsComponent::move_dir(float a, int dir) {
    if (    dir == D_RIGHT) {
        if (m_dx < 0 && on_ground()) m_dx /= 1.3;
        if (m_dx + a < m_max_h_speed) m_dx += a;
    }
    else if (dir == D_LEFT) {
        if (m_dx > 0 && on_ground()) m_dx /= 1.3;
        if (m_dx - a > -m_max_h_speed) m_dx -= a;
    }
}

// Get/set functions for movement/speed variables
void PhysicsComponent::set_friction(float f) { m_friction = f; }

void PhysicsComponent::set_speed(float s) { m_h_speed = s; }

void PhysicsComponent::set_dx(float d) { m_dx = d; }

void PhysicsComponent::set_dy(float d) { m_dy = d; }

sf::Vector2f PhysicsComponent::dpos() { return m_dpos; }

float PhysicsComponent::dx() { return m_dx; }

float PhysicsComponent::dy() { return m_dy; }

