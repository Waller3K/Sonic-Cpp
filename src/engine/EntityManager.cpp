#include "EntityManager.hpp"
#include "Entity.hpp"

//Empty Constructor
EntityManager::EntityManager()
{
}

//Ran at the start of the frame, Is used to add and remove entities while avoiding Iterator Invalidation.
void EntityManager::update()
{
	//We start by iterating through 'm_toAdd'
	for (std::shared_ptr<Entity> e : m_toAdd)
	{
		m_entities.push_back(e);
		m_entityMap[e->getTag()].push_back(e);
	}
	//And then we clear the 'm_toAdd' vector
	m_toAdd.clear();

	//Remove dead entities from the vector of ALL entities
	removeDeadEntities(m_entities);

	//Remove dead entities from each vector in the entity map
	//C++17 way of iteratirng through [key, value] pairs in a map
	for (auto& [tag, entityVec] : m_entityMap)
	{
		removeDeadEntities(entityVec);
	}
}

void EntityManager::removeDeadEntities(EntityVec& vec)
{
	for (std::shared_ptr<Entity>& e : vec)
	{
        //This line uses std::remove_if to check 
		auto newEnd = std::remove_if(begin(vec), end(vec), [](std::shared_ptr<Entity> obj) {return !(obj->isActive()); });
		vec.erase(newEnd, end(vec));
	}
}

//A simple function that creates an entity with a given tag
std::shared_ptr<Entity> EntityManager::addEntity(std::string& tag)
{
	auto e = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));
	//Instead of adding this entity to that first vector, we add it to the 'm_toAdd' vector instead

	m_toAdd.push_back(e);

	return e;
}

//A function that returns all active entities
EntityVec& EntityManager::getEntities()
{
	return m_entities;
}

//A function that returns all active entities with a given tag
EntityVec& EntityManager::getEntities(std::string tag)
{
	return m_entityMap[tag];
}

size_t EntityManager::getTotalEntities() const
{
	return m_totalEntities;
}
