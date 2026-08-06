#include "PhysicsWorld.h"

#include <algorithm>

#include "Scene.h"
#include "GameObject.h"
#include "BoxColliderComponent.h"
#include "Collision.h"
#include "RigidbodyComponent.h"
#include "TileMapComponent.h"

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

void PhysicsWorld::ResolveCollision(
    BoxColliderComponent* a,
    BoxColliderComponent* b)
{
    auto rbA =
        a->GetOwner()->GetComponent<RigidbodyComponent>();

    auto rbB =
        b->GetOwner()->GetComponent<RigidbodyComponent>();

    // Пока двигаем только объект с Rigidbody
    if (rbA == nullptr || rbB != nullptr)
        return;

    Physics::AABB boundsA =
        a->GetBounds();

    Physics::AABB boundsB =
        b->GetBounds();

    Math::Vector2 overlap =
        boundsA.GetOverlap(boundsB);

    float centerAX =
        (boundsA.Min.X + boundsA.Max.X) * 0.5f;

    float centerAY =
        (boundsA.Min.Y + boundsA.Max.Y) * 0.5f;

    float centerBX =
        (boundsB.Min.X + boundsB.Max.X) * 0.5f;

    float centerBY =
        (boundsB.Min.Y + boundsB.Max.Y) * 0.5f;

    auto& position =
        rbA->GetTransform().Position;

    Math::Vector2 velocity =
        rbA->GetVelocity();

    if (overlap.X < overlap.Y)
    {
        if (centerAX < centerBX)
            position.X -= overlap.X;
        else
            position.X += overlap.X;

        velocity.X = 0.0f;
    }
    else
    {
        if (centerAY < centerBY)
            position.Y -= overlap.Y;
        else
            position.Y += overlap.Y;

        velocity.Y = 0.0f;
    }

    rbA->SetVelocity(velocity);
}

TileMapComponent* PhysicsWorld::FindTileMap(Scene& scene)
{
    const auto& objects =
        scene.GetGameObjects();

    for (const auto& object : objects)
    {
        auto tileMap =
            object->GetComponent<TileMapComponent>();

        if (tileMap != nullptr)
        {
            return tileMap;
        }
    }

    return nullptr;
}

void PhysicsWorld::ResolveTileCollision(
    TileMapComponent* tileMapComponent,
    RigidbodyComponent* body,
    BoxColliderComponent* collider)
{
    TileMap& map =
        tileMapComponent->GetTileMap();

    Physics::AABB bounds =
        collider->GetBounds();

    const int tileSize = 32;

    int left =
        static_cast<int>(bounds.Min.X) / tileSize;

    int right =
        static_cast<int>(bounds.Max.X - 1) / tileSize;

    int top =
        static_cast<int>(bounds.Min.Y) / tileSize;

    int bottom =
        static_cast<int>(bounds.Max.Y - 1) / tileSize;

    for (int y = top; y <= bottom; y++)
    {
        for (int x = left; x <= right; x++)
        {
            if (!map.IsValidPosition(x, y))
                continue;

            const Tile& tile =
                map.GetTile(x, y);

            char buffer[128];

            sprintf_s(
                buffer,
                "Tile (%d,%d) id=%d solid=%d\n",
                x,
                y,
                tile.GetId(),
                tile.IsSolid());

            OutputDebugStringA(buffer);

            if (!tile.IsSolid())
                continue;

            OutputDebugStringA("SOLID TILE\n");
        }
    }
}


void PhysicsWorld::Update(Scene& scene)
{
    m_LastCollisions = m_Collisions;
    m_Collisions.clear();

    TileMapComponent* tileMapComponent =
        FindTileMap(scene);


    std::vector<BoxColliderComponent*> colliders;

    const auto& objects =
        scene.GetGameObjects();

    // Собираем все коллайдеры
    for (const auto& object : objects)
    {
        if (!object->IsActive())
            continue;

        if (object->GetParent() != nullptr)
            continue;

        CollectColliders(
            object.get(),
            colliders);
    }


    if (tileMapComponent != nullptr)
    {
        for (auto* collider : colliders)
        {
            auto body =
                collider->GetOwner()->GetComponent<RigidbodyComponent>();

            if (body == nullptr)
                continue;
            ResolveTileCollision(
                tileMapComponent,
                body,
                collider);
        }
    }

    // Проверяем все пары
    for (size_t i = 0; i < colliders.size(); i++)
    {
        for (size_t j = i + 1; j < colliders.size(); j++)
        {
            if (!colliders[i]->GetBounds().Intersects(
                colliders[j]->GetBounds()))
            {
                continue;
            }

            ResolveCollision(
                colliders[i],
                colliders[j]);

            Collision collisionA;
            collisionA.Self = colliders[i]->GetOwner();
            collisionA.Other = colliders[j]->GetOwner();
            collisionA.Normal = Math::Vector2(0.0f, 0.0f);
            collisionA.Depth = 0.0f;

            m_Collisions.push_back(collisionA);

            Collision collisionB;
            collisionB.Self = colliders[j]->GetOwner();
            collisionB.Other = colliders[i]->GetOwner();
            collisionB.Normal = Math::Vector2(0.0f, 0.0f);
            collisionB.Depth = 0.0f;

            m_Collisions.push_back(collisionB);
        }
    }

    // ENTER
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

    // STAY
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

    // EXIT
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