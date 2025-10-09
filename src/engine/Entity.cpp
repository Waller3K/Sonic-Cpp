#include "Entity.hpp"

Entity::Entity(const size_t id, const std::string& tag)
	: m_id(id), m_tag(tag)
{

}

bool Entity::isActive() const
{
    return m_isActive;
}

const std::string &Entity::getTag() const
{
    return m_tag;
}

const size_t Entity::getID() const
{
    return m_id;
}

void Entity::distroy()
{
    m_isActive = false;
}
