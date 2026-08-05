#pragma once

#include <vector>

class Scene;
class GameObject;
class BoxColliderComponent;
struct Collision;

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

    void CollectColliders(
        GameObject* object,
        std::vector<BoxColliderComponent*>& colliders);
    std::vector<Collision> m_Collisions;
    std::vector<Collision> m_LastCollisions;
};