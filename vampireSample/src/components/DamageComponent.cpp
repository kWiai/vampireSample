#include "DamageComponent.h"

DamageComponent::DamageComponent()
{
    m_Damage = 10.0f;
}

DamageComponent::~DamageComponent()
{
}

void DamageComponent::SetDamage(float damage)
{
    m_Damage = damage;

    if (m_Damage < 0.0f)
        m_Damage = 0.0f;
}

float DamageComponent::GetDamage() const
{
    return m_Damage;
}