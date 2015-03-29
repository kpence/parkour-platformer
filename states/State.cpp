#include "../entities/Entity.h"
#include "State.h"
#include "StateIncludes.h"

void State::allow_change_dir() {
    if (m_parent.m_input->key_down((m_parent.dir() == D_LEFT) ? "right":"left"))
        m_parent.set_dir((m_parent.dir() == D_LEFT) ? D_RIGHT : D_LEFT);
}
