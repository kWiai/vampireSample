#pragma once

#include <memory>

#include "EntityDefinition.h"

#include "src/core/GameObject.h"

class Prefab
{
public:

    Prefab();
    ~Prefab();

    void SetDefinition(
        const EntityDefinition& definition);

    const EntityDefinition&
        GetDefinition() const;

    std::unique_ptr<GameObject>
        Instantiate() const;

private:

    EntityDefinition m_Definition;
};