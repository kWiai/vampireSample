#include "TestDamageComponent.h"

#include <iostream>

void TestDamageComponent::OnDamage(
    GameObject* attacker,
    float damage)
{
    std::cout
        << "Object received damage: "
        << damage
        << std::endl;
}

void TestDamageComponent::OnDeath()
{
    std::cout
        << "Object died!"
        << std::endl;
}