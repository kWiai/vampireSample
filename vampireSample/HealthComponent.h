#pragma once
#include <cmath>
#include "Component.h"
#include "Vector2.h"
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

    void DrawHealthBar(Renderer& renderer, const Camera& camera, const Math::Vector2& offset, const Math::Vector2& size, bool isPlayer = false);
private:

    float m_MaxHealth;
    float m_Health;
};