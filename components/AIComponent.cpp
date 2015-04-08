#include <cmath>
#include <algorithm>
#include "AIComponent.h"
#include "../Game.h"
#include "../Logger.h"
#include "../entities/Entity.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "StateComponent.h"
AIComponent::AIComponent(Entity* parent) : InputComponent(parent), target_pos(parent->pos()) {
    keys_clear();
}

void AIComponent::update(float dt) {
    keys_clear();
    visible_entities.clear();
    store_visible_entities(Game::instance().screen_manager().active_screen()->ally_entities);

    if (!visible_entities.empty())
        target_pos = visible_entities.front()->pos();

    if (  std::abs(m_parent->x()-target_pos.x)>m_parent->width()
       || std::abs(m_parent->y()-target_pos.y)>m_parent->height() )
    {
        int dir = (target_pos.x > m_parent->x())? D_RIGHT:D_LEFT;

        if (!m_parent->m_physics->on_ground()) {
            if (target_pos.y < m_parent->y())
                key_hold({"jump",(dir == D_RIGHT)? "left":"right"});
            else
                key_hold({(dir == D_RIGHT)? "right":"left"});
        }
        else
            key_hold({(dir == D_RIGHT)? "right":"left"});
    }
}

bool AIComponent::is_entity_visible(Entity* e) {
    const sf::Vector2f& pp = m_parent->pos(), ep = e->pos();

    float dist = sqrt(pow(pp.x-ep.x,2) + pow(pp.y-ep.y,2));

    if (dist > 2400) return false;
    if (dist < 4)    return true;

    std::vector<sf::FloatRect> boxes;

    for (const auto sol : Game::instance().screen_manager().active_screen()->solid_entities)
        boxes.push_back({ sol->x(),sol->y(),sol->width(),sol->height() });

    // Increment from pp to ep
    for (sf::Vector2f pos = pp; dist >= 5; pos += { 4*(ep.x-pos.x)/dist, 4*(ep.y-pos.y)/dist })
    {
        dist = sqrt(pow(pos.x-ep.x,2)+pow(pos.y-ep.y,2));

        if (dist > 2400) return false;

        if (std::any_of(boxes.begin(), boxes.end(),
            [&](sf::FloatRect& b){return b.contains(pos);}))
            return false;
    }

    return true;
}

void AIComponent::store_visible_entities(const std::vector<Entity*> &ents) {
    for (const auto e : ents)
        if (is_entity_visible(e))
            visible_entities.push_back(e);
}

void AIComponent::key_hold(std::vector<std::string> kv) {
    for (const auto& k : kv) {
        keys_pressed[k] = true;
        keys_down[k] = true;
        keys_released[k] = false;
    }
}

void AIComponent::key_press(std::vector<std::string> kv) {
    for (const auto& k : kv) {
        keys_pressed[k] = true;
        keys_down[k] = true;
        keys_released[k] = false;
    }
}

void AIComponent::key_release(std::vector<std::string> kv) {
    for (const auto& k : kv) {
        keys_pressed[k] = false;
        keys_down[k] = false;
        keys_released[k] = true;
    }
}

void AIComponent::key_clear(std::vector<std::string> kv) {
    for (const auto& k : kv) {
        keys_pressed[k] = false;
        keys_down[k] = false;
        keys_released[k] = false;
    }
}

void AIComponent::keys_clear() {
    for (auto& s : {"right","left","up","down","jump","roll","dive","pause","select","cancel"}) {
        keys_pressed[s] = false;
        keys_down[s] = false;
        keys_released[s] = false;
    }
}

// Emulated input
bool AIComponent::key_pressed(const std::string& keystr) { return keys_pressed[keystr]; }
bool AIComponent::key_pressed(std::vector<std::string> keystrs) {
    return std::all_of(keystrs.begin(), keystrs.end(),
        [&](std::string i){ return key_pressed(i); });
}

bool AIComponent::key_released(const std::string& keystr) { return keys_released[keystr]; }
bool AIComponent::key_released(std::vector<std::string> keystrs) {
    return std::all_of(keystrs.begin(), keystrs.end(),
        [&](std::string i){ return key_released(i); });
}

bool AIComponent::key_down(const std::string& keystr) { return keys_down[keystr]; }
bool AIComponent::key_down(std::vector<std::string> keystrs) {
    return std::all_of(keystrs.begin(), keystrs.end(),
        [&](std::string i){ return key_down(i); });
}
