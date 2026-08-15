#include "RigidbodyComponent.h"

#include "src/core/GameObject.h"

RigidbodyComponent::RigidbodyComponent()
{
    m_Velocity = Math::Vector2(0, 0);

    m_Mass = 1.0f;

    m_UseGravity = false;

    m_GravityScale = 1.0f;

    m_IsKinematic = false;

    m_Force = Math::Vector2(0, 0);

    m_LinearDrag = 3.0f;
}

RigidbodyComponent::~RigidbodyComponent()
{

}

void RigidbodyComponent::PhysicsUpdate(float deltaTime)
{
    
}

void RigidbodyComponent::SetVelocity(
    const Math::Vector2& velocity)
{
    m_Velocity = velocity;
}

const Math::Vector2&
RigidbodyComponent::GetVelocity() const
{
    return m_Velocity;
}

void RigidbodyComponent::SetLinearDrag(float value)
{
    if (value < 0.0f)
        value = 0.0f;

    m_LinearDrag = value;
}

float RigidbodyComponent::GetLinearDrag() const
{
    return m_LinearDrag;
}

void RigidbodyComponent::AddForce(
    const Math::Vector2& force)
{
    if (m_IsKinematic)
        return;

    m_Force += force;
}


void RigidbodyComponent::AddImpulse(
    const Math::Vector2& impulse)
{
    if (m_IsKinematic)
        return;

    if (m_Mass <= 0.0f)
        return;

    m_Velocity +=
        impulse / m_Mass;
}

void RigidbodyComponent::SetMass(float mass)
{
    m_Mass = mass;
}

float RigidbodyComponent::GetMass() const
{
    return m_Mass;
}

void RigidbodyComponent::SetUseGravity(bool value)
{
    m_UseGravity = value;
}

bool RigidbodyComponent::GetUseGravity() const
{
    return m_UseGravity;
}

void RigidbodyComponent::SetGravityScale(float value)
{
    m_GravityScale = value;
}

float RigidbodyComponent::GetGravityScale() const
{
    return m_GravityScale;
}

void RigidbodyComponent::SetKinematic(bool value)
{
    m_IsKinematic = value;
}

bool RigidbodyComponent::IsKinematic() const
{
    return m_IsKinematic;
}