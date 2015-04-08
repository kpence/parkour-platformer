#ifndef _AI_COMPONENT_H_
#define _AI_COMPONENT_H_ 1

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Component.h"
#include "InputComponent.h"

class AIComponent : public InputComponent {
public:
	AIComponent(Entity* parent);
    virtual ~AIComponent() { }

    void update(float dt);

    bool is_entity_visible(Entity* e);
    void store_visible_entities(const std::vector<Entity*> &ents);

    void key_hold(std::vector<std::string> kv);
    void key_press(std::vector<std::string> kv);
    void key_release(std::vector<std::string> kv);
    void key_clear(std::vector<std::string> kv);
    void keys_clear();

    // Emulated input
    bool key_pressed(const std::string& keystr);
    bool key_pressed(std::vector<std::string> keystrs);
    bool key_released(const std::string& keystr);
    bool key_released(std::vector<std::string> keystrs);
    bool key_down(const std::string& keystr);
    bool key_down(std::vector<std::string> keystrs);

private:
    sf::Vector2f target_pos;
    std::vector<Entity*> visible_entities;
    std::map<std::string,bool> keys_pressed, keys_down, keys_released;
	AIComponent(AIComponent const&) = delete;
	void operator=(AIComponent const&) = delete;

};

#endif
