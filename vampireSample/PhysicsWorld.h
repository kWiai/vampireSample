#pragma once

#include <vector>

#include "Collision.h"
#include "SpatialHash.h"
#include "RaycastHit.h"

class Scene;
class GameObject;

class BoxColliderComponent;
class RigidbodyComponent;
class TileMapComponent;

namespace Physics
{
    class AABB;
}

class PhysicsWorld
{
public:

    PhysicsWorld();
    ~PhysicsWorld();

    struct DebugRay
    {
        Math::Vector2 Origin;
        Math::Vector2 End;

        bool Hit;
    };

    void Update(
        Scene& scene,
        float deltaTime);
    void RenderDebug(
        Renderer& renderer,
        const Camera& camera);
    bool Raycast(
        const Math::Vector2& origin,
        const Math::Vector2& direction,
        float maxDistance,
        RaycastHit& hit,
        Scene& scene,
        GameObject* ignoreObject);

private:

    // ---------- Scene ----------

    void CollectSceneColliders(
        Scene& scene,
        std::vector<BoxColliderComponent*>& colliders);

    void CollectColliders(
        GameObject* object,
        std::vector<BoxColliderComponent*>& colliders);

    TileMapComponent* FindTileMap(
        Scene& scene);

    void BeginFrame();

    // ---------- Broad Phase ----------

    void BuildSpatialHash(
        const std::vector<BoxColliderComponent*>& colliders);

    // ---------- Simulation ----------

    void IntegrateBodies(
        const std::vector<BoxColliderComponent*>& colliders,
        float deltaTime);

    void MoveBodiesX(
        const std::vector<BoxColliderComponent*>& colliders,
        float deltaTime);

    void MoveBodiesY(
        const std::vector<BoxColliderComponent*>& colliders,
        float deltaTime);

    // ---------- Tile Collision ----------

    void ResolveTileCollisions(
        Scene& scene,
        const std::vector<BoxColliderComponent*>& colliders,
        bool horizontal);

    void ResolveTileCollision(
        TileMapComponent* tileMapComponent,
        RigidbodyComponent* body,
        BoxColliderComponent* collider,
        bool horizontal);

    // ---------- Dynamic\static Collision ----------

    void ResolveDynamicCollisions(
        const std::vector<BoxColliderComponent*>& colliders,
        bool horizontal);

    void AddCollision(
        GameObject* self,
        GameObject* other);

    void AddTrigger(
        GameObject* self,
        GameObject* other);

    void ResolveCollisionX(
        BoxColliderComponent* first,
        BoxColliderComponent* second);

    void ResolveCollisionY(
        BoxColliderComponent* first,
        BoxColliderComponent* second);

    void ResolveStaticCollisionX(
        RigidbodyComponent* body,
        BoxColliderComponent* collider,
        const Physics::AABB& staticBounds);
    void ResolveStaticCollisionY(
        RigidbodyComponent* body,
        BoxColliderComponent* collider,
        const Physics::AABB& staticBounds);

    // ---------- Events ----------

    void DispatchCollisionEvents();

    void DispatchTriggerEvents();

    bool ContainsCollision(
        const std::vector<Collision>& list,
        const Collision& collision);


private:

    SpatialHash m_SpatialHash;

    std::vector<Collision> m_Collisions;
    std::vector<Collision> m_LastCollisions;
    std::vector<Collision> m_Triggers;
    std::vector<Collision> m_LastTriggers;
    std::vector<DebugRay> m_DebugRays;
};