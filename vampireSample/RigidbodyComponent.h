#pragma once

#include "Component.h"
#include "Vector2.h"

class RigidbodyComponent : public Component
{
public:

    RigidbodyComponent();
    ~RigidbodyComponent() override;

    //void Update(float deltaTime) override;
    void PhysicsUpdate(float deltaTime) override;
    void SetVelocity(const Math::Vector2& velocity);
    const Math::Vector2& GetVelocity() const;

    void AddForce(const Math::Vector2& force);
    void AddImpulse(const Math::Vector2& impulse);

    void SetMass(float mass);
    float GetMass() const;

    void SetUseGravity(bool value);
    bool GetUseGravity() const;

    void SetGravityScale(float value);
    float GetGravityScale() const;

    void SetKinematic(bool value);
    bool IsKinematic() const;

private:

    Math::Vector2 m_Velocity;

    Math::Vector2 m_Force;

    float m_Mass;

    bool m_UseGravity;

    float m_GravityScale;

    bool m_IsKinematic;
};