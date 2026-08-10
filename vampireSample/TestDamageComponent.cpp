#include "TestDamageComponent.h"
#include <Windows.h>
#include <string>


void TestDamageComponent::OnDamage(
    GameObject* attacker,
    float damage)
{
    std::string message =
        "TestDamageComponent::OnDamage() damage = "
        + std::to_string(damage)
        + "\n";

    OutputDebugStringA(
        message.c_str());

}

void TestDamageComponent::OnDeath()
{
    OutputDebugStringA(
        "TestDamageComponent::OnDeath()\n");
}