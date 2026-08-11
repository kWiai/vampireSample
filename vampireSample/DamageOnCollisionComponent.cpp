#include "DamageOnCollisionComponent.h"

#include "GameObject.h"
#include "Damage.h"

DamageOnCollisionComponent::DamageOnCollisionComponent()
{
    m_Damage = 10.0f;
}

DamageOnCollisionComponent::~DamageOnCollisionComponent()
{
}

void DamageOnCollisionComponent::OnCollisionEnter(
    GameObject* other)
{
    ApplyDamage(other);
}

void DamageOnCollisionComponent::OnTriggerEnter(
    GameObject* other)
{
    ApplyDamage(other);
}

void DamageOnCollisionComponent::ApplyDamage(
    GameObject* other)
{
    if (other == nullptr)
        return;

    if (m_Damage <= 0.0f)
        return;

    Damage::Apply(
        GetOwner(),
        other,
        m_Damage);
}

void DamageOnCollisionComponent::SetDamage(
    float damage)
{
    m_Damage = damage;

    if (m_Damage < 0.0f)
        m_Damage = 0.0f;
}

float DamageOnCollisionComponent::GetDamage() const
{
    return m_Damage;
}

void DamageOnCollisionComponent::SetEnabled(
    bool enabled)
{
    Component::SetEnabled(enabled);
}