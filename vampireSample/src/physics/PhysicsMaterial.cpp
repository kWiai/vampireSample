#include "PhysicsMaterial.h"

PhysicsMaterial::PhysicsMaterial()
{
    m_Friction = 0.0f;
    m_Restitution = 0.0f;
}

void PhysicsMaterial::SetFriction(float value)
{
    m_Friction = value;
}

float PhysicsMaterial::GetFriction() const
{
    return m_Friction;
}

void PhysicsMaterial::SetRestitution(float value)
{
    m_Restitution = value;
}

float PhysicsMaterial::GetRestitution() const
{
    return m_Restitution;
}