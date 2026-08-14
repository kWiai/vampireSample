#include "Prefab.h"

#include "EntityFactory.h"

Prefab::Prefab()
{
}

Prefab::~Prefab()
{
}

void Prefab::SetDefinition(
    const EntityDefinition& definition)
{
    m_Definition = definition;
}

const EntityDefinition&
Prefab::GetDefinition() const
{
    return m_Definition;
}

std::unique_ptr<GameObject>
Prefab::Instantiate() const
{
    return EntityFactory::Create(
        m_Definition);
}