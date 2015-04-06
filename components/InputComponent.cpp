#include "InputComponent.h"
#include <algorithm>
#include "../Game.h"

InputComponent::InputComponent(Entity* parent) : Component(parent) {
    str_to_key["right"] = { sf::Keyboard::Right };
    str_to_key["left"] = { sf::Keyboard::Left };
    str_to_key["up"] = { sf::Keyboard::Up };
    str_to_key["down"] = { sf::Keyboard::Down };
    str_to_key["jump"] = { sf::Keyboard::Z };
    str_to_key["roll"] = { sf::Keyboard::LShift };
    str_to_key["dive"] = { sf::Keyboard::LShift };
    str_to_key["pause"] = { sf::Keyboard::P };
    str_to_key["select"] = { sf::Keyboard::Z };
    str_to_key["cancel"] = { sf::Keyboard::X };
}

void InputComponent::update(float dt) {
}

void InputComponent::set_events(std::vector<sf::Event>* p) {
    m_events = p;
}

// pressed
bool InputComponent::key_pressed(int key) {
    return std::any_of(m_events->begin(), m_events->end(),
        [&](sf::Event& ev){ return (ev.type == sf::Event::KeyPressed
                             && ev.key.code == key); });
}

bool InputComponent::key_pressed(std::vector<int> keys) {
    return std::all_of(keys.begin(), keys.end(),
        [&](int i){ return key_pressed(i); });
}

bool InputComponent::key_pressed(const std::string& keystr) {
    return key_pressed(str_to_key[keystr]);
}

bool InputComponent::key_pressed(std::vector<std::string> keystrs) {
    return std::any_of(keystrs.begin(), keystrs.end(),
        [&](std::string i){ return key_pressed(str_to_key[i]); });
}

// released
bool InputComponent::key_released(int key) {
    return std::any_of(m_events->begin(), m_events->end(),
        [&](sf::Event& ev){ return (ev.type == sf::Event::KeyReleased
                             && ev.key.code == key); });
}

bool InputComponent::key_released(std::vector<int> keys) {
    return std::all_of(keys.begin(), keys.end(),
        [&](int i){ return key_released(i); });
}

bool InputComponent::key_released(const std::string& keystr) {
    return key_released(str_to_key[keystr]);
}

bool InputComponent::key_released(std::vector<std::string> keystrs) {
    return std::any_of(keystrs.begin(), keystrs.end(),
        [&](std::string i){ return key_released(str_to_key[i]); });
}

// down
bool InputComponent::key_down(int key) {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(key));
}

bool InputComponent::key_down(std::vector<int> keys) {
    return std::all_of(keys.begin(), keys.end(),
        [&](int i){ return key_down(i); });
}

bool InputComponent::key_down(const std::string& keystr) {
    return key_down(str_to_key[keystr]);
}

bool InputComponent::key_down(std::vector<std::string> keystrs) {
    return std::any_of(keystrs.begin(), keystrs.end(),
        [&](std::string i){ return key_down(str_to_key[i]); });
}
