// PlayerControllerComponent.h
#pragma once
#include "Component.h"
#include <algorithm>
#include "Vector2.h"
class RigidbodyComponent;

class PlayerControllerComponent : public Component
{
public:
    PlayerControllerComponent();
    ~PlayerControllerComponent() override;

    void Update(float deltaTime) override;

    void SetSideView(bool enable);
    bool IsSideView() const;

    void SetMoveSpeed(float speed);
    float GetMoveSpeed() const;

    void SetJumpForce(float force);
    float GetJumpForce() const;

    void SetAcceleration(float accel);
    void SetDeceleration(float decel);

    void Render(Renderer& renderer, const Camera& camera) override;

private:
    bool IsGrounded() const;

    bool m_IsSideView = true;

    float m_MoveSpeed = 300.0f;
    float m_JumpForce = 600.0f;
    float m_Acceleration = 1200.0f;
    float m_Deceleration = 1500.0f;

    float m_CurrentSpeedX = 0.0f;
    float m_CurrentSpeedY = 0.0f;
    Math::Vector2 m_LastDirection = Math::Vector2(1.0f, 0.0f);
    void FireProjectile();

    RigidbodyComponent* m_Rigidbody = nullptr;
};