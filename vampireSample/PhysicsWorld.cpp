#include "PhysicsWorld.h"

#include <cmath>
#include <algorithm>
#include <iostream>

#include "Scene.h"
#include "GameObject.h"
#include "BoxColliderComponent.h"
#include "Collision.h"
#include "RigidbodyComponent.h"
#include "TileMapComponent.h"
#include "CollisionMatrix.h"
#include "DebugSettings.h"

PhysicsWorld::PhysicsWorld()
{
}
PhysicsWorld::~PhysicsWorld()
{
}
void PhysicsWorld::MoveBodiesX(
    const std::vector<BoxColliderComponent*>& colliders,
    float deltaTime)
{
    for (auto* collider : colliders)
    {
        auto body =
            collider->GetOwner()->GetComponent<RigidbodyComponent>();

        if (body == nullptr)
            continue;

        if (body->IsKinematic())
            continue;

        body->GetTransform().Position.X +=
            body->GetVelocity().X * deltaTime;
    }
}
void PhysicsWorld::MoveBodiesY(
    const std::vector<BoxColliderComponent*>& colliders,
    float deltaTime)
{
    for (auto* collider : colliders)
    {
        auto body =
            collider->GetOwner()->GetComponent<RigidbodyComponent>();

        if (body == nullptr)
            continue;

        if (body->IsKinematic())
            continue;

        body->GetTransform().Position.Y +=
            body->GetVelocity().Y * deltaTime;
    }
}

void PhysicsWorld::SimulateStep(
    Scene& scene,
    const std::vector<BoxColliderComponent*>& colliders,
    float deltaTime)
{
    IntegrateBodies(
        colliders,
        deltaTime);

    // -------------------------
    // X
    // -------------------------

    MoveBodiesX(
        colliders,
        deltaTime);

    BuildSpatialHash(
        colliders);

    ResolveTileCollisions(
        scene,
        colliders,
        true);

    ResolveDynamicCollisions(
        colliders,
        true);


    // -------------------------
    // Y
    // -------------------------

    MoveBodiesY(
        colliders,
        deltaTime);

    BuildSpatialHash(
        colliders);

    ResolveTileCollisions(
        scene,
        colliders,
        false);

    ResolveDynamicCollisions(
        colliders,
        false);
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
void PhysicsWorld::ResolveCollisionX(
    BoxColliderComponent* first,
    BoxColliderComponent* second)
{
    auto body =
        first->GetOwner()->GetComponent<RigidbodyComponent>();

    if (body == nullptr)
        return;

    if (second->GetOwner()->GetComponent<RigidbodyComponent>() != nullptr)
        return;

    Physics::AABB firstBounds =
        first->GetBounds();

    Physics::AABB secondBounds =
        second->GetBounds();

    if (!firstBounds.Intersects(secondBounds))
        return;

    float firstCenter =
        (firstBounds.Min.X + firstBounds.Max.X) * 0.5f;

    float secondCenter =
        (secondBounds.Min.X + secondBounds.Max.X) * 0.5f;

    if (firstCenter < secondCenter)
    {
        body->GetTransform().Position.X -=
            firstBounds.Max.X -
            secondBounds.Min.X;
    }
    else
    {
        body->GetTransform().Position.X +=
            secondBounds.Max.X -
            firstBounds.Min.X;
    }

    auto velocity =
        body->GetVelocity();

    velocity.X = 0.0f;

    body->SetVelocity(velocity);
}

void PhysicsWorld::ResolveCollisionY(
    BoxColliderComponent* first,
    BoxColliderComponent* second)
{
    auto body =
        first->GetOwner()->GetComponent<RigidbodyComponent>();

    if (body == nullptr)
        return;

    if (second->GetOwner()->GetComponent<RigidbodyComponent>() != nullptr)
        return;

    Physics::AABB firstBounds =
        first->GetBounds();

    Physics::AABB secondBounds =
        second->GetBounds();

    if (!firstBounds.Intersects(secondBounds))
        return;

    float firstCenter =
        (firstBounds.Min.Y + firstBounds.Max.Y) * 0.5f;

    float secondCenter =
        (secondBounds.Min.Y + secondBounds.Max.Y) * 0.5f;

    if (firstCenter < secondCenter)
    {
        body->GetTransform().Position.Y -=
            firstBounds.Max.Y -
            secondBounds.Min.Y;
    }
    else
    {
        body->GetTransform().Position.Y +=
            secondBounds.Max.Y -
            firstBounds.Min.Y;
    }

    auto velocity =
        body->GetVelocity();

    velocity.Y = 0.0f;

    body->SetVelocity(velocity);
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
    BoxColliderComponent* collider,
    bool horizontal)
{
    TileMap& map =
        tileMapComponent->GetTileMap();

    TileSet* tileSet =
        tileMapComponent->GetTileSet();

    if (tileSet == nullptr)
        return;

    const int tileWidth =
        tileSet->GetTileWidth();

    const int tileHeight =
        tileSet->GetTileHeight();

    Physics::AABB bounds =
        collider->GetBounds();

    int left =
        static_cast<int>(bounds.Min.X) / tileWidth;

    int right =
        static_cast<int>(bounds.Max.X - 1) / tileWidth;

    int top =
        static_cast<int>(bounds.Min.Y) / tileHeight;

    int bottom =
        static_cast<int>(bounds.Max.Y - 1) / tileHeight;

    for (int y = top; y <= bottom; y++)
    {
        for (int x = left; x <= right; x++)
        {
            if (!map.IsValidPosition(x, y))
                continue;

            const Tile& tile =
                map.GetTile(x, y);

            const TileInfo& info =
                tileSet->GetTile(tile.GetId());

            if (!info.Solid)
                continue;

            Physics::AABB tileBounds(
                Math::Vector2(
                    x * tileWidth,
                    y * tileHeight),

                Math::Vector2(
                    (x + 1) * tileWidth,
                    (y + 1) * tileHeight));

            if (horizontal)
            {
                ResolveStaticCollisionX(
                    body,
                    collider,
                    tileBounds);
            }
            else
            {
                ResolveStaticCollisionY(
                    body,
                    collider,
                    tileBounds);
            }

        }
    }
}
void PhysicsWorld::ResolveTileCollisions(
    Scene& scene,
    const std::vector<BoxColliderComponent*>& colliders,
    bool horizontal)
{
    TileMapComponent* tileMap =
        FindTileMap(scene);

    if (tileMap == nullptr)
        return;

    for (auto* collider : colliders)
    {
        auto body =
            collider->GetOwner()->GetComponent<RigidbodyComponent>();

        if (body == nullptr)
            continue;

        ResolveTileCollision(
            tileMap,
            body,
            collider,
            horizontal);
        
    }
}
void PhysicsWorld::ResolveDynamicCollisions(
    const std::vector<BoxColliderComponent*>& colliders,
    bool horizontal)
{
    std::vector<BoxColliderComponent*> nearby;

    for (auto* collider : colliders)
    {
        nearby.clear();

        m_SpatialHash.Query(
            collider,
            nearby);

        for (auto* other : nearby)
        {
            if (collider == other)
                continue;

            if (collider > other)
                continue;

            if (!CollisionMatrix::CanCollide(
                collider->GetLayer(),
                other->GetLayer()))
            {
                continue;
            }

            if (!collider->GetBounds().Intersects(
                other->GetBounds()))
            {
                continue;
            }

            if (collider->IsTrigger() ||
                other->IsTrigger())
            {
                AddTrigger(
                    collider->GetOwner(),
                    other->GetOwner());

                AddTrigger(
                    other->GetOwner(),
                    collider->GetOwner());

                continue;
            }

            auto firstBody =
                collider->GetOwner()
                ->GetComponent<RigidbodyComponent>();

            auto secondBody =
                other->GetOwner()
                ->GetComponent<RigidbodyComponent>();

            if (firstBody != nullptr &&
                secondBody == nullptr)
            {
                if (horizontal)
                {
                    ResolveCollisionX(
                        collider,
                        other);
                }
                else
                {
                    ResolveCollisionY(
                        collider,
                        other);
                }
            }
            else if (firstBody == nullptr &&
                secondBody != nullptr)
            {
                if (horizontal)
                {
                    ResolveCollisionX(
                        other,
                        collider);
                }
                else
                {
                    ResolveCollisionY(
                        other,
                        collider);
                }
            }
            else if (firstBody != nullptr &&
                secondBody != nullptr)
            {
                if (horizontal)
                {
                    ResolveDynamicCollisionX(
                        collider,
                        other);
                }
                else
                {
                    ResolveDynamicCollisionY(
                        collider,
                        other);
                }
            }

            AddCollision(
                collider->GetOwner(),
                other->GetOwner());

            AddCollision(
                other->GetOwner(),
                collider->GetOwner());
        }
    }
}

void PhysicsWorld::AddCollision(
    GameObject* self,
    GameObject* other)
{
    Collision collision;

    collision.Self = self;
    collision.Other = other;
    collision.Normal = Math::Vector2(0.0f, 0.0f);
    collision.Depth = 0.0f;

    m_Collisions.push_back(
        collision);
}

void PhysicsWorld::AddTrigger(
    GameObject* self,
    GameObject* other)
{
    Collision trigger;

    trigger.Self = self;
    trigger.Other = other;
    trigger.Normal = Math::Vector2(0, 0);
    trigger.Depth = 0;

    m_Triggers.push_back(trigger);
}

void PhysicsWorld::DispatchCollisionEvents()
{
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

void PhysicsWorld::DispatchTriggerEvents()
{
    for (const auto& collision : m_Triggers)
    {
        if (ContainsCollision(
            m_LastTriggers,
            collision))
        {
            continue;
        }

        for (const auto& component :
            collision.Self->GetComponents())
        {
            component->OnTriggerEnter(
                collision.Other);
        }
    }
    for (const auto& collision : m_Triggers)
    {
        if (!ContainsCollision(
            m_LastTriggers,
            collision))
        {
            continue;
        }

        for (const auto& component :
            collision.Self->GetComponents())
        {
            component->OnTriggerStay(
                collision.Other);
        }
    }
    for (const auto& collision : m_LastTriggers)
    {
        if (ContainsCollision(
            m_Triggers,
            collision))
        {
            continue;
        }

        for (const auto& component :
            collision.Self->GetComponents())
        {
            component->OnTriggerExit(
                collision.Other);
        }
    }
}
void PhysicsWorld::ResolveStaticCollisionX(
    RigidbodyComponent* body,
    BoxColliderComponent* collider,
    const Physics::AABB& staticBounds)
{
    Physics::AABB bodyBounds =
        collider->GetBounds();

    if (!bodyBounds.Intersects(staticBounds))
        return;

    float overlap;

    if ((bodyBounds.Min.X + bodyBounds.Max.X) * 0.5f <
        (staticBounds.Min.X + staticBounds.Max.X) * 0.5f)
    {
        overlap =
            bodyBounds.Max.X -
            staticBounds.Min.X;

        body->GetTransform().Position.X -= overlap;
    }
    else
    {
        overlap =
            staticBounds.Max.X -
            bodyBounds.Min.X;

        body->GetTransform().Position.X += overlap;
    }

    Math::Vector2 velocity =
        body->GetVelocity();

    velocity.X = 0.0f;

    body->SetVelocity(velocity);
}
void PhysicsWorld::ResolveStaticCollisionY(
    RigidbodyComponent* body,
    BoxColliderComponent* collider,
    const Physics::AABB& staticBounds)
{
    Physics::AABB bodyBounds =
        collider->GetBounds();

    if (!bodyBounds.Intersects(staticBounds))
        return;

    float overlap;

    if ((bodyBounds.Min.Y + bodyBounds.Max.Y) * 0.5f <
        (staticBounds.Min.Y + staticBounds.Max.Y) * 0.5f)
    {
        overlap =
            bodyBounds.Max.Y -
            staticBounds.Min.Y;

        body->GetTransform().Position.Y -= overlap;
    }
    else
    {
        overlap =
            staticBounds.Max.Y -
            bodyBounds.Min.Y;

        body->GetTransform().Position.Y += overlap;
    }

    Math::Vector2 velocity =
        body->GetVelocity();

    velocity.Y = 0.0f;

    body->SetVelocity(velocity);
}
void PhysicsWorld::ResolveDynamicCollisionX(
    BoxColliderComponent* first,
    BoxColliderComponent* second)
{
    auto firstBody =
        first->GetOwner()->GetComponent<RigidbodyComponent>();

    auto secondBody =
        second->GetOwner()->GetComponent<RigidbodyComponent>();

    if (firstBody == nullptr ||
        secondBody == nullptr)
    {
        return;
    }

    if (firstBody->IsKinematic() &&
        secondBody->IsKinematic())
    {
        return;
    }

    Physics::AABB firstBounds =
        first->GetBounds();

    Physics::AABB secondBounds =
        second->GetBounds();

    if (!firstBounds.Intersects(secondBounds))
        return;

    float firstCenter =
        (firstBounds.Min.X + firstBounds.Max.X) * 0.5f;

    float secondCenter =
        (secondBounds.Min.X + secondBounds.Max.X) * 0.5f;

    float overlap = 0.0f;

    if (firstCenter < secondCenter)
    {
        overlap =
            firstBounds.Max.X -
            secondBounds.Min.X;
    }
    else
    {
        overlap =
            secondBounds.Max.X -
            firstBounds.Min.X;
    }

    if (overlap <= 0.0f)
        return;

    bool firstKinematic =
        firstBody->IsKinematic();

    bool secondKinematic =
        secondBody->IsKinematic();

    if (firstKinematic)
    {
        if (firstCenter < secondCenter)
        {
            secondBody->GetTransform().Position.X += overlap;
        }
        else
        {
            secondBody->GetTransform().Position.X -= overlap;
        }
    }
    else if (secondKinematic)
    {
        if (firstCenter < secondCenter)
        {
            firstBody->GetTransform().Position.X -= overlap;
        }
        else
        {
            firstBody->GetTransform().Position.X += overlap;
        }
    }
    else
    {
        float totalMass =
            firstBody->GetMass() +
            secondBody->GetMass();

        if (totalMass <= 0.0f)
            return;

        float firstMove =
            overlap *
            (secondBody->GetMass() / totalMass);

        float secondMove =
            overlap *
            (firstBody->GetMass() / totalMass);

        if (firstCenter < secondCenter)
        {
            firstBody->GetTransform().Position.X -= firstMove;
            secondBody->GetTransform().Position.X += secondMove;
        }
        else
        {
            firstBody->GetTransform().Position.X += firstMove;
            secondBody->GetTransform().Position.X -= secondMove;
        }
    }

    Math::Vector2 firstVelocity =
        firstBody->GetVelocity();

    Math::Vector2 secondVelocity =
        secondBody->GetVelocity();

    if (!firstKinematic)
        firstVelocity.X = 0.0f;

    if (!secondKinematic)
        secondVelocity.X = 0.0f;

    firstBody->SetVelocity(firstVelocity);
    secondBody->SetVelocity(secondVelocity);
}
void PhysicsWorld::ResolveDynamicCollisionY(
    BoxColliderComponent* first,
    BoxColliderComponent* second)
{
    auto firstBody =
        first->GetOwner()->GetComponent<RigidbodyComponent>();

    auto secondBody =
        second->GetOwner()->GetComponent<RigidbodyComponent>();

    if (firstBody == nullptr ||
        secondBody == nullptr)
    {
        return;
    }

    if (firstBody->IsKinematic() &&
        secondBody->IsKinematic())
    {
        return;
    }

    Physics::AABB firstBounds =
        first->GetBounds();

    Physics::AABB secondBounds =
        second->GetBounds();

    if (!firstBounds.Intersects(secondBounds))
        return;

    float firstCenter =
        (firstBounds.Min.Y + firstBounds.Max.Y) * 0.5f;

    float secondCenter =
        (secondBounds.Min.Y + secondBounds.Max.Y) * 0.5f;

    float overlap = 0.0f;

    if (firstCenter < secondCenter)
    {
        overlap =
            firstBounds.Max.Y -
            secondBounds.Min.Y;
    }
    else
    {
        overlap =
            secondBounds.Max.Y -
            firstBounds.Min.Y;
    }

    if (overlap <= 0.0f)
        return;

    bool firstKinematic =
        firstBody->IsKinematic();

    bool secondKinematic =
        secondBody->IsKinematic();

    if (firstKinematic)
    {
        if (firstCenter < secondCenter)
        {
            secondBody->GetTransform().Position.Y += overlap;
        }
        else
        {
            secondBody->GetTransform().Position.Y -= overlap;
        }
    }
    else if (secondKinematic)
    {
        if (firstCenter < secondCenter)
        {
            firstBody->GetTransform().Position.Y -= overlap;
        }
        else
        {
            firstBody->GetTransform().Position.Y += overlap;
        }
    }
    else
    {
        float totalMass =
            firstBody->GetMass() +
            secondBody->GetMass();

        if (totalMass <= 0.0f)
            return;

        float firstMove =
            overlap *
            (secondBody->GetMass() / totalMass);

        float secondMove =
            overlap *
            (firstBody->GetMass() / totalMass);

        if (firstCenter < secondCenter)
        {
            firstBody->GetTransform().Position.Y -= firstMove;
            secondBody->GetTransform().Position.Y += secondMove;
        }
        else
        {
            firstBody->GetTransform().Position.Y += firstMove;
            secondBody->GetTransform().Position.Y -= secondMove;
        }
    }

    Math::Vector2 firstVelocity =
        firstBody->GetVelocity();

    Math::Vector2 secondVelocity =
        secondBody->GetVelocity();

    if (!firstKinematic)
        firstVelocity.Y = 0.0f;

    if (!secondKinematic)
        secondVelocity.Y = 0.0f;

    firstBody->SetVelocity(firstVelocity);
    secondBody->SetVelocity(secondVelocity);
}
void PhysicsWorld::CollectSceneColliders(
    Scene& scene,
    std::vector<BoxColliderComponent*>& colliders)
{
    const auto& objects =
        scene.GetGameObjects();

    for (const auto& object : objects)
    {
        if (!object->IsActive())
            continue;

        if (object->GetParent())
            continue;

        CollectColliders(
            object.get(),
            colliders);
    }
}
void PhysicsWorld::BuildSpatialHash(
    const std::vector<BoxColliderComponent*>& colliders)
{
    m_SpatialHash.Clear();

    for (auto* collider : colliders)
    {
        m_SpatialHash.Insert(
            collider);
    }
}
void PhysicsWorld::BeginFrame()
{
    m_LastCollisions =
        std::move(m_Collisions);

    m_Collisions.clear();

    m_LastTriggers =
        std::move(m_Triggers);

    m_Triggers.clear();
   // m_DebugRays.clear();
}
void PhysicsWorld::IntegrateBodies(
    const std::vector<BoxColliderComponent*>& colliders,
    float deltaTime)
{
    for (auto* collider : colliders)
    {
        auto body =
            collider->GetOwner()->GetComponent<RigidbodyComponent>();

        if (body == nullptr)
            continue;

        if (body->IsKinematic())
            continue;

        Math::Vector2 velocity =
            body->GetVelocity();

        if (body->GetUseGravity())
        {
            velocity.Y +=
                980.0f *
                body->GetGravityScale() *
                deltaTime;
        }

        body->SetVelocity(velocity);
    }
}

bool PhysicsWorld::Raycast(
    const Math::Vector2& origin,
    const Math::Vector2& direction,
    float maxDistance,
    RaycastHit& hit,
    Scene& scene,
    GameObject* ignoreObject)
{
    DebugRay ray;

    ray.Origin = origin;
    ray.End = origin + direction * maxDistance;
    ray.Hit = false;

    hit = RaycastHit();

    float closestDistance = maxDistance;

    std::vector<BoxColliderComponent*> colliders;

    CollectSceneColliders(
        scene,
        colliders);

    for (auto* collider : colliders)
    {
        if (collider == nullptr)
            continue;

        if (ignoreObject != nullptr &&
            collider->GetOwner() == ignoreObject)
        {
            continue;
        }

        float distance;
        Math::Vector2 normal;

        if (!collider->GetBounds().Raycast(
            origin,
            direction,
            maxDistance,
            distance,
            normal))
        {
            continue;
        }

        if (distance < 0.0f)
            continue;

        if (distance >= closestDistance)
            continue;

        closestDistance = distance;

        hit.Hit = true;
        hit.Distance = distance;
        hit.Normal = normal;
        hit.Collider = collider;
        hit.Object = collider->GetOwner();

        hit.Point =
            origin +
            direction * distance;
    }

    TileMapComponent* tileMapComponent =
        FindTileMap(scene);

    if (tileMapComponent != nullptr)
    {
        TileMap& map =
            tileMapComponent->GetTileMap();

        TileSet* tileSet =
            tileMapComponent->GetTileSet();

        if (tileSet != nullptr)
        {
            const int tileWidth =
                tileSet->GetTileWidth();

            const int tileHeight =
                tileSet->GetTileHeight();

            Math::Vector2 rayEnd =
                origin +
                direction * maxDistance;

            float minX =
                min(origin.X, rayEnd.X);

            float maxX =
                max(origin.X, rayEnd.X);

            float minY =
                min(origin.Y, rayEnd.Y);

            float maxY =
                max(origin.Y, rayEnd.Y);

            int left =
                static_cast<int>(
                    std::floor(minX / tileWidth));

            int right =
                static_cast<int>(
                    std::floor(maxX / tileWidth));

            int top =
                static_cast<int>(
                    std::floor(minY / tileHeight));

            int bottom =
                static_cast<int>(
                    std::floor(maxY / tileHeight));

            for (int y = top; y <= bottom; y++)
            {
                for (int x = left; x <= right; x++)
                {
                    if (!map.IsValidPosition(x, y))
                        continue;

                    const Tile& tile =
                        map.GetTile(x, y);

                    if (tile.GetId() < 0)
                        continue;

                    const TileInfo& info =
                        tileSet->GetTile(tile.GetId());

                    if (!info.Solid)
                        continue;

                    Physics::AABB tileBounds(
                        Math::Vector2(
                            x * tileWidth,
                            y * tileHeight),

                        Math::Vector2(
                            (x + 1) * tileWidth,
                            (y + 1) * tileHeight));

                    float distance;
                    Math::Vector2 normal;

                    if (!tileBounds.Raycast(
                        origin,
                        direction,
                        maxDistance,
                        distance,
                        normal))
                    {
                        continue;
                    }

                    if (distance < 0.0f)
                        continue;

                    if (distance >= closestDistance)
                        continue;

                    closestDistance = distance;

                    hit.Hit = true;
                    hit.Distance = distance;
                    hit.Normal = normal;

                    // У TileMap нет BoxColliderComponent
                    hit.Collider = nullptr;

                    // Сам TileMapComponent принадлежит GameObject
                    hit.Object =
                        tileMapComponent->GetOwner();

                    hit.Point =
                        origin +
                        direction * distance;
                }
            }
        }
    }

    if (hit.Hit)
    {
        ray.End = hit.Point;
        ray.Hit = true;
    }

    m_DebugRays.push_back(ray);

    return hit.Hit;
}

void PhysicsWorld::RenderDebug(
    Renderer& renderer,
    const Camera& camera)
{
    if (DebugSettings::DrawSpatialHash)
    {
        m_SpatialHash.DebugDraw(
            renderer,
            camera);
    }
    if (DebugSettings::DrawRaycasts)
    {
        for (const auto& ray : m_DebugRays)
        {
            if (ray.Hit)
            {
                renderer.DrawLine(
                    ray.Origin.X,
                    ray.Origin.Y,
                    ray.End.X,
                    ray.End.Y,
                    camera,
                    255,
                    255,
                    0);   // желтый
            }
            else
            {
                renderer.DrawLine(
                    ray.Origin.X,
                    ray.Origin.Y,
                    ray.End.X,
                    ray.End.Y,
                    camera,
                    150,
                    150,
                    150); // серый
            }
        }
    }
    m_DebugRays.clear();
}

void PhysicsWorld::Update(
    Scene& scene,
    float deltaTime)
{
    BeginFrame();

    std::vector<BoxColliderComponent*> colliders;

    CollectSceneColliders(
        scene,
        colliders);


    // -------------------------
    // Sub-stepping
    // -------------------------

    const float fixedStep = 1.0f / 120.0f;

    float remainingTime = deltaTime;

    while (remainingTime > 0.0f)
    {
        float step =
            min(
                remainingTime,
                fixedStep);

        SimulateStep(
            scene,
            colliders,
            step);

        remainingTime -= step;
    }


    // -------------------------
    // Events
    // -------------------------

    DispatchCollisionEvents();
    DispatchTriggerEvents();
}