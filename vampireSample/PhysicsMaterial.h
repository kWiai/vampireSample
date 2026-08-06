#pragma once

class PhysicsMaterial
{
public:

    PhysicsMaterial();

    void SetFriction(float value);
    float GetFriction() const;

    void SetRestitution(float value);
    float GetRestitution() const;

private:

    float m_Friction;

    float m_Restitution;
};