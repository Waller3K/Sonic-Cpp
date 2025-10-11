#pragma once

#include <memory>
#include <map>
#include <vector>
#include <string>

#include "Entity.hpp"

typedef std::vector<std::shared_ptr<Entity>>    EntityVec;
typedef std::map<std::string, EntityVec>        EntityMap;

class EntityManager
{
    //Member Variables
    //A Vector that contains shared pointers to all of the entities
    EntityVec m_entities;

    //An ordered map that contains tags and a the coresponding vector of entity pointers
    EntityMap m_entityMap;

    //A vector of entity pointers that are marked to be added to the game on the next update()
    EntityVec m_toAdd;

    //Number of entities added since the start of the scene
    size_t m_totalEntities = 0;

public:

    EntityManager();

    void update();

    void removeDeadEntities(EntityVec& vec);

    std::shared_ptr<Entity> addEntity(std::string tag);

	EntityVec& getEntities();

	EntityVec& getEntities(std::string tag);

	size_t getTotalEntities() const;
};