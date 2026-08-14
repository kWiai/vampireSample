#include "EntityManager.h"

#include "EntityLoader.h"
#include "EntityDefinition.h"
#include "EntityFactory.h"
#include "src/core/GameObject.h"

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
}

std::unique_ptr<GameObject>
EntityManager::Create(
    const std::string& entityName)
{
    EntityDefinition definition;

    const std::string filePath =
        entityName + ".json";

    if (!EntityLoader::Load(
        filePath,
        definition))
    {
        return nullptr;
    }

    return EntityFactory::Create(
        definition);
}