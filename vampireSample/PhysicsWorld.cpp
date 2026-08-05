#include "PhysicsWorld.h"

#include <algorithm>

#include "Scene.h"
#include "GameObject.h"
#include "BoxColliderComponent.h"
#include "Collision.h"

PhysicsWorld::PhysicsWorld()
{

}

PhysicsWorld::~PhysicsWorld()
{

}

void PhysicsWorld::CollectColliders(
    GameObject* object,
    std::vector<BoxColliderComponent*>& colliders)
{
    if (object == nullptr)
        return;

    auto collider =
        object->GetComponent<BoxColliderComponent>();

    if (collider != nullptr)
    {
        colliders.push_back(collider);
    }

    for (GameObject* child : object->GetChildren())
    {
        CollectColliders(
            child,
            colliders);
    }
}

bool PhysicsWorld::ContainsCollision(
    const std::vector<Collision>& list,
    const Collision& collision)
{
    for (const auto& c : list)
    {
        if (c == collision)
            return true;
    }

    return false;
}

void PhysicsWorld::Update(Scene& scene)
{
    m_LastCollisions = m_Collisions;
    m_Collisions.clear();
    std::vector<BoxColliderComponent*> colliders;

    const auto& objects =
        scene.GetGameObjects();

    // Собираем все коллайдеры рекурсивно
    for (const auto& object : objects)
    {
        if (object->GetParent() != nullptr)
            continue;

        CollectColliders(
            object.get(),
            colliders);
    }

    // Проверяем все пары
    for (size_t i = 0; i < colliders.size(); i++)
    {
        for (size_t j = i + 1; j < colliders.size(); j++)
        {
            if (colliders[i]->GetBounds().Intersects(
                colliders[j]->GetBounds()))
            {
                Collision collisionA;

                collisionA.Self =
                    colliders[i]->GetOwner();

                collisionA.Other =
                    colliders[j]->GetOwner();

                collisionA.Normal =
                    Math::Vector2(0, 0);

                collisionA.Depth = 0;

                m_Collisions.push_back(collisionA);

                Collision collisionB;

                collisionB.Self =
                    colliders[j]->GetOwner();

                collisionB.Other =
                    colliders[i]->GetOwner();

                collisionB.Normal =
                    Math::Vector2(0, 0);

                collisionB.Depth = 0;

                m_Collisions.push_back(collisionB);

                for (const auto& collision : m_Collisions)
                {
                    if (ContainsCollision(
                        m_LastCollisions,
                        collision))
                    {
                        continue;
                    }

                    for (const auto& component :
                        collision.Self->GetComponents())
                    {
                        component->OnCollisionEnter(
                            collision.Other);
                    }
                }
                for (const auto& collision : m_Collisions)
                {
                    if (!ContainsCollision(
                        m_LastCollisions,
                        collision))
                    {
                        continue;
                    }

                    for (const auto& component :
                        collision.Self->GetComponents())
                    {
                        component->OnCollisionStay(
                            collision.Other);
                    }
                }
                for (const auto& collision : m_LastCollisions)
                {
                    if (ContainsCollision(
                        m_Collisions,
                        collision))
                    {
                        continue;
                    }

                    for (const auto& component :
                        collision.Self->GetComponents())
                    {
                        component->OnCollisionExit(
                            collision.Other);
                    }
                }
            }
        }
    }
}