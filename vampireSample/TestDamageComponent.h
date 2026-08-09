#pragma once

#include "Component.h"

class TestDamageComponent : public Component
{
public:

    void OnDamage(
        GameObject* attacker,
        float damage) override;

    void OnDeath() override;
};