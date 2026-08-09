#pragma once

#include "Component.h"

class DamageComponent : public Component
{
public:

    DamageComponent();
    ~DamageComponent() override;

    void SetDamage(float damage);
    float GetDamage() const;

private:

    float m_Damage;
};