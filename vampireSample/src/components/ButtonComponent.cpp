#include "src/components/ButtonComponent.h"

#include "src/core/GameObject.h"
#include "src/core/Scene.h"
#include "src/core/EventManager.h"
#include "src/core/Event.h"

ButtonComponent::ButtonComponent()
{
    m_OnlyPlayer = true;
    m_Target = nullptr;
}

ButtonComponent::~ButtonComponent()
{
}

void ButtonComponent::OnInteract(
    GameObject* interactor)
{
    if (interactor == nullptr)
        return;

    if (m_OnlyPlayer &&
        interactor->GetTag() != "Player")
    {
        return;
    }

    Scene* scene =
        GetOwner()->GetScene();

    if (scene == nullptr)
        return;

    Event event;

    event.Type =
        EventType::ButtonPressed;

    event.Sender =
        GetOwner();

    event.Target =
        m_Target;

    event.Value =
        0.0f;

    scene->GetEvents().Send(event);
}

void ButtonComponent::SetOnlyPlayer(bool value)
{
    m_OnlyPlayer = value;
}

bool ButtonComponent::GetOnlyPlayer() const
{
    return m_OnlyPlayer;
}

void ButtonComponent::SetTarget(GameObject* target)
{
    m_Target = target;
}

GameObject* ButtonComponent::GetTarget() const
{
    return m_Target;
}