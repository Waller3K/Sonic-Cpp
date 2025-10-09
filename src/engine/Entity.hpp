#pragma once

#include <memory>
#include <string>
#include <tuple>

#include "Components.hpp"

typedef std::tuple<
    CTransform
> ComponentTuple;

class EntityManager;

class Entity
{
    friend class EntityManager;

    //Member Variables
    bool            m_isActive;
    std::string     m_tag;
    size_t          m_id;
    ComponentTuple  m_components;

    Entity(const size_t id, const std::string& tag);

public:

    bool    isActive()              const;
    const   std::string& getTag()   const;
    const   size_t       getID()    const;
    void    distroy();

    //Entity Template Functions
    template<typename T>
    T& getComponent()
    {
        return std::get<T>(m_components);
    }

    template<typename T>
    bool hasComponent() const
    {
        return getComponent<T>().has;
    }

    template<typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs) 
	{
		auto& component = getComponent<T>();
		component = T(std::forward<TArgs>(mArgs)...);
		component.has = true;
		return component;
	}

	template<typename T>
	const T& getComponent() const 
	{
		return std::get<T>(m_components);
	}

	template<typename T>
	void removeComponent() 
	{
		getComponent<T>() = T();
	}


};