#pragma once

#include "Component.h"

class DamageOnCollisionComponent :
    public Component
{
public:

    DamageOnCollisionComponent();

    ~DamageOnCollisionComponent() override;

    void OnCollisionEnter(
        GameObject* other) override;

    void SetDamage(float damage);

    float GetDamage() const;

private:

    float m_Damage;
};