#include "EventManager.h"

#include "GameObject.h"
#include "Component.h"
#include <string>
#include "Window.h"

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
}

void EventManager::Send(
    const Event& event)
{
    m_Events.push_back(event);
}

void EventManager::Update()
{
    for (const Event& event : m_Events)
    {
        Dispatch(event);
    }
}

void EventManager::Dispatch(
    const Event& event)
{
    if (event.Target == nullptr)
        return;

    const auto& components =
        event.Target->GetComponents();

    for (const auto& component : components)
    {
        if (component == nullptr)
            continue;

        if (!component->IsEnabled())
            continue;

        switch (event.Type)
        {
        case EventType::Damage:

            component->OnDamage(
                event.Sender,
                event.Value);
            OutputDebugString(L"DAMAGE");
            break;


        case EventType::Death:

            component->OnDeath();
            OutputDebugString(L"DEATH");
            break;


        case EventType::Attack:

            component->OnAttack(
                event.Target);

            break;


        case EventType::Interact:

            component->OnInteract(
                event.Sender);

            break;


        case EventType::ButtonPressed:

            component->OnButtonPressed();

            break;


        case EventType::DialogueStarted:
        case EventType::DialogueFinished:
        case EventType::None:

            break;
        }
    }
}

const std::vector<Event>&
EventManager::GetEvents() const
{
    return m_Events;
}

void EventManager::Clear()
{
    m_Events.clear();
}