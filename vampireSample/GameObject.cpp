#include "GameObject.h"

#include "Render.h"

#include <algorithm>

#include "BoxColliderComponent.h"

#include "DebugSettings.h"
#include "RigidbodyComponent.h"
#include "Scene.h"
#include "TileMapComponent.h"

GameObject::GameObject()
{
    m_Name = "GameObject";
    m_Tag = "Default";
    m_IsActive = true;
    m_Parent = nullptr;
    m_Scene = nullptr;
}

GameObject::~GameObject()
{

}

void GameObject::SetScene(Scene* scene)
{
    m_Scene = scene;

    // Передаем сцену детям
    for (GameObject* child : m_Children)
    {
        if (child)
        {
            child->SetScene(scene);
        }
    }
}

Scene* GameObject::GetScene() const
{
    return m_Scene;
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

void GameObject::PhysicsUpdate(float deltaTime)
{
    for (auto& component : m_Components)
    {
        if (component->IsEnabled())
        {
            component->PhysicsUpdate(deltaTime);
        }
    }

    for (GameObject* child : m_Children)
    {
        if (child && child->IsActive())
        {
            child->PhysicsUpdate(deltaTime);
        }
    }
}

void GameObject::LateUpdate(float deltaTime)
{
    for (auto& component : m_Components)
    {
        if (component->IsEnabled())
        {
            component->LateUpdate(deltaTime);
        }
    }

    for (GameObject* child : m_Children)
    {
        if (child && child->IsActive())
        {
            child->LateUpdate(deltaTime);
        }
    }
}

void GameObject::RenderDebug(
    Renderer& renderer,
    const Camera& camera)
{
    if (DebugSettings::DrawPhysics)
    {
        auto tileMap =
            GetComponent<TileMapComponent>();

        if (tileMap != nullptr)
        {
            tileMap->RenderDebug(
                renderer,
                camera);
        }
    }
    if (DebugSettings::DrawPhysics)
    {
        auto collider =
            GetComponent<BoxColliderComponent>();

        if (collider != nullptr)
        {
            Physics::AABB bounds =
                collider->GetBounds();

            if (collider->IsTrigger())
            {
                renderer.DrawRectangle(
                    bounds.Min.X,
                    bounds.Min.Y,
                    bounds.Max.X - bounds.Min.X,
                    bounds.Max.Y - bounds.Min.Y,
                    camera,
                    255, 0, 0);   // красный
            }
            else
            {
                renderer.DrawRectangle(
                    bounds.Min.X,
                    bounds.Min.Y,
                    bounds.Max.X - bounds.Min.X,
                    bounds.Max.Y - bounds.Min.Y,
                    camera,
                    0, 255, 0);   // зеленый
            }
        }
    }

    const auto& pos =
        GetTransform().Position;

    renderer.DrawLine(
        pos.X - 4.0f,
        pos.Y,
        pos.X + 4.0f,
        pos.Y,
        camera,
        255,
        255,
        0);

    renderer.DrawLine(
        pos.X,
        pos.Y - 4.0f,
        pos.X,
        pos.Y + 4.0f,
        camera,
        255,
        255,
        0);

    if (DebugSettings::DrawPhysics)
    {
        auto body =
            GetComponent<RigidbodyComponent>();

        if (body != nullptr)
        {
            auto pos =
                GetTransform().Position;

            auto velocity =
                body->GetVelocity();

            renderer.DrawLine(
                pos.X,
                pos.Y,
                pos.X + velocity.X * 0.15f,
                pos.Y + velocity.Y * 0.15f,
                camera,
                0,
                255,
                255);
        }
    }

    for (GameObject* child : m_Children)
    {
        child->RenderDebug(
            renderer,
            camera);
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
    if (m_Scene)
    {
        child->SetScene(m_Scene);
    }
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
const std::vector<std::unique_ptr<Component>>&
GameObject::GetComponents() const
{
    return m_Components;
}

const std::vector<GameObject*>&
GameObject::GetChildren() const
{
    return m_Children;
}