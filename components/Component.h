#ifndef _COMPONENT_H_
#define _COMPONENT_H_ 1

#include <memory>

class Entity;

class Component
{
public:
	Component(Entity* parent);

    virtual ~Component() { };
protected:
	Entity* m_parent;
};

#endif
