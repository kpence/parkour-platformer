#ifndef _COMPONENT_H_
#define _COMPONENT_H_ 1

#include <memory>

class Entity;

class Component
{
public:
	Component(Entity* parent);

    virtual ~Component() { };

    virtual void update(float dt) { };

protected:
	Entity* m_parent;
};

#endif
