#pragma once

#include <memory>

struct EntityDefinition;

class GameObject;

class EntityFactory
{
public:

    static std::unique_ptr<GameObject>
        Create(
            const EntityDefinition& definition);
};