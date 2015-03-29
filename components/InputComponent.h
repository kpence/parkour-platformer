#ifndef _INPUT_COMPONENT_H_
#define _INPUT_COMPONENT_H_ 1

#include <SFML/Graphics.hpp>
#include <vector>
#include "Component.h"

class InputComponent : public Component {
public:
	InputComponent(Entity* parent);
    virtual ~InputComponent() { }

    std::map<std::string, std::vector<int>> str_to_key;

	bool key_pressed(int key);
	bool key_pressed(std::vector<int> keys);
	bool key_pressed(std::string keystr);
	bool key_pressed(std::vector<std::string> keystrs);

	bool key_down(int key);
	bool key_down(std::vector<int> keys);
	bool key_down(std::string keystr);
	bool key_down(std::vector<std::string> keystrs);

	bool key_released(int key);
	bool key_released(std::vector<int> keys);
	bool key_released(std::string keystr);
	bool key_released(std::vector<std::string> keystrs);

    void set_events(std::vector<sf::Event>* p);

protected:
	void clear_input_events();
	void push_input_events(const sf::Event& ev);

private:
    std::vector<sf::Event>* m_events;

	InputComponent(InputComponent const&) = delete;
	void operator=(InputComponent const&) = delete;

};

#endif

/* SFML Key enum:
Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
Escape,
LShift, RShift,
LAlt, RAlt,
LControl, RControl,
LSystem, RSystem,
Menu,
LBracket, RBracket,
SemiColon,
Comma,
Period,
Quote,
Slash, BackSlash,
Tilde,
Equal,
Dash,
Space,
Return,
BackSpace,
Tab,
PageUp, PageDown, End, Home,
Insert, Delete,
Add, Subtract, Multiply, Divide,
Left, Right, Up, Down, */
