#include "Component.h"

Component::Component()
{
    m_Owner = nullptr;
    m_Enabled = true;
}

Component::~Component()
{

}

void Component::Start()
{

}

void Component::Update(float deltaTime)
{

}

void Component::Render(Renderer& renderer)
{

}

void Component::SetOwner(GameObject* owner)
{
    m_Owner = owner;
}

GameObject* Component::GetOwner() const
{
    return m_Owner;
}

void Component::SetEnabled(bool enabled)
{
    m_Enabled = enabled;
}

bool Component::IsEnabled() const
{
    return m_Enabled;
}