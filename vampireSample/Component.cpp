#include "Component.h"

#include "GameObject.h"
#include "Transform.h"

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

void Component::Render(
    Renderer& renderer,
    const Camera& camera)
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
 

Transform& Component::GetTransform()
{
    return m_Owner->GetTransform();
}

const Transform& Component::GetTransform() const
{
    return m_Owner->GetTransform();
}

void Component::SetEnabled(bool enabled)
{
    m_Enabled = enabled;
}

bool Component::IsEnabled() const
{
    return m_Enabled;
}
void Component::OnCollisionEnter(GameObject* other)
{

}

void Component::OnCollisionStay(GameObject* other)
{

}

void Component::OnCollisionExit(GameObject* other)
{

}
void Component::PhysicsUpdate(float)
{

}

void Component::LateUpdate(float)
{

}