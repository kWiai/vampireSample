#include "GameObject.h"

#include "Render.h"

GameObject::GameObject()
{
    m_Name = "GameObject";
    m_Tag = "Default";
    m_IsActive = true;
}

GameObject::~GameObject()
{

}

void GameObject::Update(float deltaTime)
{
    for (auto& component : m_Components)
    {
        if (component->IsEnabled())
        {
            component->Update(deltaTime);
        }
    }
}

void GameObject::Render(Renderer& renderer)
{
    for (auto& component : m_Components)
    {
        if (component->IsEnabled())
        {
            component->Render(renderer);
        }
    }
}

void GameObject::SetName(const std::string& name)
{
    m_Name = name;
}

const std::string& GameObject::GetName() const
{
    return m_Name;
}

void GameObject::SetTag(const std::string& tag)
{
    m_Tag = tag;
}

const std::string& GameObject::GetTag() const
{
    return m_Tag;
}

void GameObject::SetActive(bool active)
{
    m_IsActive = active;
}


bool GameObject::IsActive() const
{
    return m_IsActive;
}

Transform& GameObject::GetTransform()
{
    return m_Transform;
}

const Transform& GameObject::GetTransform() const
{
    return m_Transform;
}