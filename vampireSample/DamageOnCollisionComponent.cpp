#include "DamageOnCollisionComponent.h"

#include "GameObject.h"
#include "Damage.h"

DamageOnCollisionComponent::
DamageOnCollisionComponent()
{
    m_Damage = 10.0f;
}

DamageOnCollisionComponent::
~DamageOnCollisionComponent()
{
}

void DamageOnCollisionComponent::OnCollisionEnter(
    GameObject* other)
{
    if (other == nullptr)
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
}

float DamageOnCollisionComponent::GetDamage() const
{
    return m_Damage;
}