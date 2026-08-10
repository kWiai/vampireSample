#include "Damage.h"

#include "GameObject.h"
#include "HealthComponent.h"
#include "Scene.h"
#include "EventManager.h"

namespace Damage
{
    void Apply(
        GameObject* attacker,
        GameObject* target,
        float amount)
    {
        if (target == nullptr)
            return;

        if (amount <= 0.0f)
            return;

        auto health =
            target->GetComponent<HealthComponent>();

        if (health == nullptr)
            return;

        if (health->IsDead())
            return;

        health->TakeDamage(amount);

        Scene* scene =
            target->GetScene();

        if (scene == nullptr)
            return;

        Event event;

        event.Type = EventType::Damage;
        event.Sender = attacker;
        event.Target = target;
        event.Value = amount;

        scene->GetEvents().Send(event);

        if (health->IsDead())
        {
            Event deathEvent;

            deathEvent.Type = EventType::Death;
            deathEvent.Sender = attacker;
            deathEvent.Target = target;

            scene->GetEvents().Send(
                deathEvent);
        }
    }
}