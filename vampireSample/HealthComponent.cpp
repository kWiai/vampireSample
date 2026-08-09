#include "HealthComponent.h"

HealthComponent::HealthComponent()
{
    m_MaxHealth = 100.0f;
    m_Health = 100.0f;
}

HealthComponent::~HealthComponent()
{
}

void HealthComponent::SetMaxHealth(float health)
{
    m_MaxHealth = health;

    if (m_MaxHealth < 0.0f)
        m_MaxHealth = 0.0f;

    if (m_Health > m_MaxHealth)
        m_Health = m_MaxHealth;
}

float HealthComponent::GetMaxHealth() const
{
    return m_MaxHealth;
}

void HealthComponent::SetHealth(float health)
{
    m_Health = health;

    if (m_Health < 0.0f)
        m_Health = 0.0f;

    if (m_Health > m_MaxHealth)
        m_Health = m_MaxHealth;
}

float HealthComponent::GetHealth() const
{
    return m_Health;
}

void HealthComponent::Heal(float amount)
{
    if (amount <= 0.0f)
        return;

    SetHealth(m_Health + amount);
}

void HealthComponent::TakeDamage(float amount)
{
    if (amount <= 0.0f)
        return;

    SetHealth(m_Health - amount);
}

bool HealthComponent::IsDead() const
{
    return m_Health <= 0.0f;
}