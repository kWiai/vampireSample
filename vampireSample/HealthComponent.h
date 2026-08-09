#pragma once

#include "Component.h"

class HealthComponent : public Component
{
public:

    HealthComponent();
    ~HealthComponent() override;

    void SetMaxHealth(float health);
    float GetMaxHealth() const;

    void SetHealth(float health);
    float GetHealth() const;

    void Heal(float amount);
    void TakeDamage(float amount);

    bool IsDead() const;

private:

    float m_MaxHealth;
    float m_Health;
};