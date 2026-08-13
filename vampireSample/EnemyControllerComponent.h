#pragma once
#include <vector>
#include "Component.h"
#include "Vector2.h"

class GameObject;
class RigidbodyComponent;
class BoxColliderComponent;
class Scene;

class EnemyControllerComponent : public Component
{
public:
    EnemyControllerComponent();
    ~EnemyControllerComponent() override;

    void Update(float deltaTime) override;

    void AddPoint(const Math::Vector2& point);
    void SetSpeed(float speed);
    float GetSpeed() const;

    void SetViewRadius(float radius);
    float GetViewRadius() const;

    void SetTarget(GameObject* target);
    void SetJumpForce(float force);

    void Render(Renderer& renderer, const Camera& camera) override;

private:
    enum class State { Patrol, Chase };

    void UpdatePatrol(float deltaTime);
    void UpdateChase(float deltaTime);
    bool IsTargetInRange() const;
    bool IsGrounded() const;
    bool IsWallAhead(float distance = 25.0f) const;
    void TryJump();
    void MoveTowards(const Math::Vector2& target, float deltaTime);

    bool IsSideView() const;   // новый метод

    RigidbodyComponent* m_Rigidbody = nullptr;
    BoxColliderComponent* m_Collider = nullptr;

    std::vector<Math::Vector2> m_Points;
    int m_CurrentPoint = 0;
    float m_Speed = 100.0f;
    float m_ViewRadius = 300.0f;
    float m_JumpForce = 400.0f;
    GameObject* m_Target = nullptr;
    State m_State = State::Patrol;
};