#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Transform.h"
#include "Component.h"

class Renderer;

class GameObject
{
public:

    GameObject();
    virtual ~GameObject();

    virtual void Update(float deltaTime);
    void Render(
        Renderer& renderer,
        const Camera& camera);

    void SetName(const std::string& name);
    const std::string& GetName() const;

    void SetActive(bool active);
    bool IsActive() const;

    void SetTag(const std::string& tag);

    const std::string& GetTag() const;

    Transform& GetTransform();
    const Transform& GetTransform() const;

    template<typename T, typename... Args>
    T* AddComponent(Args&&... args);

    template<typename T>
    T* GetComponent();

    template<typename T>
    bool HasComponent() const;

    template<typename T>
    void RemoveComponent();

protected:

    std::string m_Name;

    std::string m_Tag;

    Transform m_Transform;

    bool m_IsActive;

private:

    std::vector<std::unique_ptr<Component>> m_Components;
};

template<typename T, typename... Args>
T* GameObject::AddComponent(Args&&... args)
{
    if (HasComponent<T>())
    {
        return GetComponent<T>();
    }

    auto component =
        std::make_unique<T>(std::forward<Args>(args)...);

    component->SetOwner(this);

    T* ptr = component.get();

    m_Components.push_back(std::move(component));

    return ptr;
}

template<typename T>
T* GameObject::GetComponent()
{
    for (auto& component : m_Components)
    {
        if (auto ptr = dynamic_cast<T*>(component.get()))
        {
            return ptr;
        }
    }

    return nullptr;
}

template<typename T>
void GameObject::RemoveComponent()
{
    for (auto it = m_Components.begin(); it != m_Components.end(); ++it)
    {
        if (dynamic_cast<T*>(it->get()))
        {
            m_Components.erase(it);
            return;
        }
    }
}

template<typename T>
bool GameObject::HasComponent() const
{
    for (const auto& component : m_Components)
    {
        if (dynamic_cast<T*>(component.get()) != nullptr)
        {
            return true;
        }
    }

    return false;
}