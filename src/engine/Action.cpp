#include "Action.hpp"

Action::Action()
    : m_isActive(false)
{
}

Action::Action(int id, int type)
    : m_id(id), m_type(type), m_isActive(false)
{
}

const int& Action::getID()
{
    return m_id;
}

const int& Action::getType()
{
    return m_type;
}

bool& Action::isActive()
{
    return m_isActive;
}