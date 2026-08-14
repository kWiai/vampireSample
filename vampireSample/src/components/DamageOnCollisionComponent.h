#pragma once

#include "src/core/Component.h"

class DamageOnCollisionComponent : public Component
{
public:

    DamageOnCollisionComponent();
    ~DamageOnCollisionComponent() override;

    void OnCollisionEnter(
        GameObject* other) override;

    void OnTriggerEnter(
        GameObject* other) override;

    void SetDamage(float damage);
    float GetDamage() const;

    void SetEnabled(bool enabled);

private:

    void ApplyDamage(
        GameObject* other);

private:

    float m_Damage;
};