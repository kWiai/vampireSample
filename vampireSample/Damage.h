#pragma once

class GameObject;

namespace Damage
{
    void Apply(
        GameObject* attacker,
        GameObject* target,
        float amount);
}