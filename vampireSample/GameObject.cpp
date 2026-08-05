#include "GameObject.h"

#include "Render.h"

#include <algorithm>

GameObject::GameObject()
{
    m_Name = "GameObject";
    m_Tag = "Default";
    m_IsActive = true;
    m_Parent = nullptr;
}

GameObject::~GameObject()
{

}

void GameObject::Update(float deltaTime)
{
    // Сначала обновляем компоненты текущего объекта
    for (auto& component : m_Components)
    {
        if (component->IsEnabled())
        {
            component->Update(deltaTime);
        }
    }

    // Затем обновляем всех детей
    for (GameObject* child : m_Children)
    {
        if (child == nullptr)
            continue;

        if (!child->IsActive())
            continue;

        child->Update(deltaTime);
    }
}

void GameObject::Render(
    Renderer& renderer,
    const Camera& camera)
{
    // Сначала рисуем текущий объект
    for (auto& component : m_Components)
    {
        if (component->IsEnabled())
        {
            component->Render(
                renderer,
                camera);
        }
    }

    // Затем рисуем всех детей
    for (GameObject* child : m_Children)
    {
        if (child == nullptr)
            continue;

        if (!child->IsActive())
            continue;

        child->Render(
            renderer,
            camera);
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

void GameObject::SetParent(GameObject* parent)
{
    m_Parent = parent;
}

GameObject* GameObject::GetParent() const
{
    return m_Parent;
}

void GameObject::AddChild(GameObject* child)
{
    if (child == nullptr)
        return;

    m_Children.push_back(child);

    child->SetParent(this);
}

void GameObject::RemoveChild(GameObject* child)
{
    auto it =
        std::find(
            m_Children.begin(),
            m_Children.end(),
            child);

    if (it != m_Children.end())
    {
        (*it)->SetParent(nullptr);

        m_Children.erase(it);
    }
}

const std::vector<GameObject*>&
GameObject::GetChildren() const
{
    return m_Children;
}