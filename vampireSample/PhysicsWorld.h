#pragma once

#include <vector>
#include "AABB.h"

class Scene;
class GameObject;
class BoxColliderComponent;
class RigidbodyComponent;
struct Collision;
class TileMapComponent;


class PhysicsWorld
{
public:

    PhysicsWorld();
    ~PhysicsWorld();

    void Update(Scene& scene);

    bool ContainsCollision(
        const std::vector<Collision>& list,
        const Collision& collision);

private:
    void ResolveCollision(
        BoxColliderComponent* a,
        BoxColliderComponent* b);

    TileMapComponent* FindTileMap(Scene& scene);

    void ResolveTileCollision(
        TileMapComponent* tileMap,
        RigidbodyComponent* body,
        BoxColliderComponent* collider);

    void ResolveTileOverlap(
        TileMapComponent* tileMap,
        RigidbodyComponent* body,
        BoxColliderComponent* collider,
        int tileX,
        int tileY);

    void ResolveStaticCollision(
        RigidbodyComponent* body,
        BoxColliderComponent* collider,
        const Physics::AABB& staticBounds);

    void CollectColliders(
        GameObject* object,
        std::vector<BoxColliderComponent*>& colliders);
    std::vector<Collision> m_Collisions;
    std::vector<Collision> m_LastCollisions;
};